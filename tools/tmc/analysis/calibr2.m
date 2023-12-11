%%
Range = 100000;
N = 100;
%%
while true
  I = -Range + 2*Range*rand(N,4);
  if any(I(:,1)==I(:,2))
    fprintf(1,'Found random duplicate input, retrying\n');
    continue;
  end
  V = I(:,2) < I(:,1);
  I(V,:) = I(V,[2 1 4 3]);
  break;
end
clear V
%%
Res = zeros(N,11);
for i = 1:N
  [n,d,r,m,b,ox0,ox1,oy0] = find_noxdroy(I(i,1:2),I(i,3:4));
  Res(i,1:8) = [n,d,r,m,b,ox0,ox1,oy0];
  Res(i,9:11) = test_noxdroy(n,d,r,m,b,ox0,ox1,oy0);
end
r = abs(Res(:,3))./Res(:,2);
figure; plot(r,Res(:,9:10),'.');
xlabel('r'); legend('all','contig');
figure; plot(Res(:,4),Res(:,9:10),'.');
xlabel('m'); legend('all','contig');
figure; plot(Res(:,7)-Res(:,6),Res(:,9:10),'.');
xlabel('dX'); legend('all','contig');
%%
i = 1;
%%
% Deep dive on testing: try the full range on r
R = Res(i,:);
rRes = zeros(Res(i,2),3);
rs = 0:Res(i,2)-1;
if Res(i,1)<0
  rs = -rs;
end
fprintf(1,'Row %d: d = %d\n', i, length(rs));
for j=1:length(rs)
  if mod(j,5000) == 0
    fprintf(1, '  Testing %d/%d\n', j, length(rs));
  end
  myres = test_noxdroy(R(1),R(2),rs(j),R(4),R(5),R(6),R(7),R(8));
  rRes(j,:) = myres;
end
figure;
plot(rs,rRes(:,1:2),'.',rs,rRes(:,3),'o',R(3)*[1 1],[0 1],'k');
legend('all','contig','initial');
xlabel('r');
title(sprintf('Row %d, d = %d, dX = %d', i, R(2), R(7)-R(6)));
i = i+1;
%%
% newres columns:
%  m, b, dX, n_segs, avgseglen
newres = zeros(N,5);
for i = 1:N
%%
% Attempt to turn what I learned above into a standard process
% - Calculate n,d,r,x0,y0 needed (find_noxdroy())
% - See how well it works (test_noxdroy())
% - if it does not cover the whole range, evaluate error and try moving r
% stepwise and re-evaluate. If it doesn't improve, fallback to the best
% choice, then advance x0 and start over
X = I(i,1:2);
Y = I(i,3:4);
[n,d,r,m,b,ox0,ox1,oy0] = find_noxdroy(X,Y);
result = test_noxdroy2(n,d,r,m,b,ox0,ox1,oy0);
newres(i,1) = m;
newres(i,2) = b;
newres(i,3) = ox1-ox0;
while result(3) < ox1-ox0+1
  % Evaluate the error, move in the appropriate direction, re-evaluate that
  % sample, and if it works, then redo the whole test.
  fi = result(3); % number of matching entries at beginning
  fix = ox0+fi;
  fy = round(m*fix + b);
  fiy = eval_ndrxyx(n,d,r,ox0,oy0,fix);
  dfy = fiy-fy; % positive if our approximation is too high
  assert(dfy ~= 0);
  r1 = r - sign(dfy);
  fiy = eval_ndrxyx(n,d,r1,ox0,oy0,fix);
  if fiy == fy
    result1 = test_noxdroy2(n,d,r1,m,b,ox0,ox1,oy0);
    if result1(3) >= result(3)
      r = r1;
      result = result1;
      continue;
    end
  end
  % accept the partial result with ox1 = last good value
  assert(result(3)>0);
  newres(i,4) = newres(i,4)+1;
  accept(i,n,d,r,ox0,ox0+result(3)-1,oy0);
  % then update ox0 = ox0+result(3)
  [n,d,r,m,b,ox0,ox1,oy0] = find_noxdroy(X,Y,ox0+result(3));
  result = test_noxdroy2(n,d,r,m,b,ox0,ox1,oy0);
end
% accept the current result to finish this conversion
newres(i,4) = newres(i,4)+1;
newres(i,5) = newres(i,3)/newres(i,4);
accept(i,n,d,r,ox0,ox1,oy0);
%%
end
%%
for i = 1:N
  R = Res(i,:);
  score = test_noxdroy(R(1),R(2),R(3),R(4),R(5),R(6),R(7),R(8));
end
%%
% Save I in ascii suitable for C testing
N = size(I,1);
fid = fopen('I.txt', 'w');
for i = 1:N
  fprintf(fid, ' %12.4e %12.4e %12.4e %12.4e\n', I(i,:));
end
fclose(fid);
clear fid i ans
%%
function [n,d,r,m,b,ox0,ox1,oy0] = find_noxdroy(X,Y,iX1)
  assert(all(size(X) == [1 2]));
  assert(all(size(Y) == [1 2]));
  if (diff(X) < 0)
    X = fliplr(X);
    Y = fliplr(Y);
  end
  iX = [ceil(X(1)) floor(X(2))];
  if nargin > 2
    iX(1) = iX1;
  end
  dX = diff(X);
  dY = diff(Y);
  prec = 0.1/dX;
  m = dY/dX;
  b = Y(1)-m*X(1);
  [n,d] = rationalize(m,prec);
  riY0 = m*iX(1)+b;
  iY0 = floor(riY0); % integer part of riY0
  fY0 = riY0-iY0; % fractional part of riY0
  assert(fY0 >= 0);
  if n < 0
    % need -1 < rr <= 0
    rr = fY0-0.5;
    if rr > 0
      rr = rr-1;
      iY0 = iY0+1;
    end
    r = round(rr*d);
  else
    % need 0 <= rr < 1
    rr = fY0+0.5;
    if rr >= 1
      rr = rr-1;
      iY0 = iY0+1;
    end
    r = round(rr*d);
  end
  ox0 = iX(1);
  ox1 = iX(2);
  oy0 = iY0;
end

function [n,d] = rationalize(m, prec)
  % if m < 0
  %   sign = -1;
  %   m = -m;
  % else
  %   sign = 1;
  % end
  assert(prec > 0);
  d = 1;
  n = round(m);
  while true
    rem = m-n/d;
    if abs(rem) < prec; return; end
    assert(abs(rem) < 1);
    d1 = round(1/rem);
    n = n*d1 + d;
    d = d * d1;
    g = gcd(n,d);
    n = n/g;
    d = d/g;
    if d < 0
      n = -n;
      d = -d;
    end
  end
end

function score = test_noxdroy(n,d,r,m,b,ox0,ox1,oy0)
  % test_noxdroy()
  x = ox0:ox1;
  y = m*x+b;
  iy = round(y);
  if (n >= 0)
    iiy = floor((n*(x-ox0)+r)/d) + oy0;
  else
    iiy = ceil((n*(x-ox0)+r)/d) + oy0;
  end
  ok = iiy == iy;
  starts = find(diff([0 ok])>0);
  ends = find(diff([ok 0])<0);
  lengths = ends-starts+1;
  first_len = find(~ok,1);
  if isempty(first_len)
    first_len = length(ok);
  else
    first_len = first_len-1;
  end
  score = [sum(ok) max(lengths) first_len]/length(x);
end

function score = test_noxdroy2(n,d,r,m,b,ox0,ox1,oy0)
  % test_noxdroy()
  % score = [n_ok max_contig_len starting_contig_len]
  x = ox0:ox1;
  y = m*x+b;
  iy = round(y);
  if (n >= 0)
    iiy = floor((n*(x-ox0)+r)/d) + oy0;
  else
    iiy = ceil((n*(x-ox0)+r)/d) + oy0;
  end
  ok = iiy == iy;
  starts = find(diff([0 ok])>0);
  ends = find(diff([ok 0])<0);
  lengths = ends-starts+1;
  first_len = find(~ok,1);
  if isempty(first_len)
    first_len = length(ok);
  else
    first_len = first_len-1;
  end
  score = [sum(ok) max(lengths) first_len];
end

function y = eval_ndrxyx(n,d,r,x0,y0,x)
  if (n >= 0)
    y = floor((n*(x-x0)+r)/d) + y0;
  else
    y = ceil((n*(x-x0)+r)/d) + y0;
  end
end

function accept(i,n,d,r,ox0,ox1,oy0)
  %fprintf(1,'%d: %d %d %d %d %d %d\n',i,n,d,r,ox0,ox1,oy0);
  fprintf(1, '%d: x=[%d:%d] n/d=%d/%d r=%d y0=%d\n',i,ox0,ox1,n,d,r,oy0);
end
