%%
Range = 10000;
N = 100;
dmax = 10000;
%%
I = -Range + 2*Range*rand(N,4);
Res = zeros(N,4);
for i = 1:N
  [n, d, r, y0, nok] = find_ndry0(I(i,1:2),I(i,3:4),dmax);
  Res(i,:) = [n d r, y0];
  disp(nok);
end
V = Res(:,2)<0;
fails = sum(V);
fprintf('Fails: %d/%d\n', fails, N);
fprintf('n: %d - %d\n', min(Res(~V,1)), max(Res(~V,1)));
fprintf('d: %d - %d\n', min(Res(~V,2)), max(Res(~V,2)));
fprintf('r: %d - %d\n', min(Res(~V,3)), max(Res(~V,3)));
figure; plot(Res(:,4),'.');
%%
I = -Range + 2*Range*rand(N,4);
Res = zeros(N,10);
for i = 1:N
  [n,d,r,m,b,ox0,ox1,oy0] = find_noxdroy(I(i,1:2),I(i,3:4));
  Res(i,1:8) = [n,d,r,m,b,ox0,ox1,oy0];
  Res(i,9:10) = test_noxdroy(n,d,r,m,b,ox0,ox1,oy0);
end
r = abs(Res(:,3))./Res(:,2);
figure; plot(r,Res(:,9),'.',r,Res(:,10),'.');
xlabel('r'); legend('all','contig');
figure; plot(Res(:,4),Res(:,9),'.',Res(:,4),Res(:,10),'.');
xlabel('m'); legend('all','contig');
%%
% Deep dive on testing: try the full range on r
i = 2;
R = Res(i,:);
rRes = zeros(Res(i,2),2);
rs = 0:Res(i,2)-1;
if Res(i,1)<0
  rs = -rs;
end
for j=1:length(rs)
  rRes(j,:) = test_noxdroy(R(1),R(2),rs(j),R(4),R(5),R(6),R(7),R(8));
end
figure;
plot(rs,rRes,'.',R(3)*[1 1],[0 1],'k');
legend('all','contig');
xlabel('r');
%%
for i = 1:N
  R = Res(i,:);
  score = test_noxdroy(R(1),R(2),R(3),R(4),R(5),R(6),R(7),R(8));
end
%%
V = Res(:,2)<0;
fails = sum(V);
fprintf('Fails: %d/%d\n', fails, N);
fprintf('n: %d - %d\n', min(Res(~V,1)), max(Res(~V,1)));
fprintf('d: %d - %d\n', min(Res(~V,2)), max(Res(~V,2)));
fprintf('r: %d - %d\n', min(Res(~V,3)), max(Res(~V,3)));
figure; plot(Res(:,4),'.');%% Investigate a failure
i=12;
[n, d, r, y0] = find_ndry0(I(i,1:2),I(i,3:4),dmax);
%%
dX = I(:,2)-I(:,1);
dY = I(:,4)-I(:,3);
m = dY./dX;
V = Res(:,2)<0;
figure;
plot(m(V),Res(V,2),'.');
xlabel('m');
ylabel('d');
%%
% Test rationalize:
dX = I(:,2)-I(:,1);
dY = I(:,4)-I(:,3);
m = dY./dX;
for i = 1:length(m)
  prec = abs(1/(2*dX(i)));
  [n,d] = rationalize(m(i),prec);
  fprintf(1,'%f = %d/%d (%f)\n', m(i), n, d, prec);
end
%%

function [n,d,r,y0,nok] = find_ndry0(X,Y,dmax)
  iX = round(X);
  dX = iX(2)-iX(1);
  min_n_y0 = -1;
  min_n_y0_d = -1;
  if dX == 0
    n = 0;
    d = -2;
    r = 0;
    y0 = mean(Y);
  else
    m = (Y(2)-Y(1))/(X(2)-X(1));
    b = Y(1) - m*X(1);
    if dX > 0
      x = iX(1):iX(2);
    else
      x = iX(2):iX(1);
    end
    ds = 1:dmax;
    ns = round(m*ds);
    dm = abs(dX*(m-ns./ds));
    i = find(dm == min(dm),1);
    dy = m*x + b;
    y = round(dy);
    d = ds(i);
    n = round(m*d);
    r = round(mean(dy-x*n/d)*d);
    y0 = -1;
    drs = -3:3;
    nok = zeros(size(drs));
    for i=1:length(drs)
      dr = drs(i);
      y1 = round((x*n+r+dr)/d);
      % nne = sum(y~=y1);
      nnok = find(y~=y1,1);
      if isempty(nnok)
        y0 = 0;
        nok = nok(1:i-1);
        return;
      end
      nok(i) = nnok;
    end
    d = -1;
  end
end

function [n,d,r,m,b,ox0,ox1,oy0] = find_noxdroy(X,Y)
  assert(all(size(X) == [1 2]));
  assert(all(size(Y) == [1 2]));
  if (diff(X) < 0)
    X = fliplr(X);
    Y = fliplr(Y);
  end
  iX = [ceil(X(1)) floor(X(2))];
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
    if abs(rem) < prec return; end
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
  % 0: works over the entire range
  % 1: works over at least the first half the range out of the box
  % 2: adjusting r could improve performance
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
  score = [sum(ok) max(lengths)]/length(x);
end
