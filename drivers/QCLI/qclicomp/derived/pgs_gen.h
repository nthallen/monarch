/* Date should go here */
#define    ZEMAXTERMINALCODE 59
#define    ZEMAXRSLAENGE     7
#define    ZEANZZST          80
#define    ZEMAXTEINTRAG     306
#define    ZEMAXNTEINTRAG    137
#define    ZEMAXTE1          80
#define    ZEMAXTE2          193
#define    ZEMAXNTE          80
#define    ZEANZNT           59
#define    ZEANZPROD         113
#define    ZEMAXTNEXT        129
#define    ZEMAXTCHECK       184
#define    ZEMAXNTNEXT       142
#define    ZETINDEX          ZEMAXTERMINALCODE / M_BITS
#define    ZESTOPSYMBOL      1
static  K_TYP1    TBase[ ZEANZZST + 1]  =
{   0,    14,    32,    28,     0,     1,    24,    32,    29,    33,
    7,    41,    64,    65,    58,    60,    60,    67,     0,     9,
   64,    22,     0,    80,    81,    85,    86,    87,    86,    77,
   78,    91,    92,    93,    94,    93,    84,    85,    50,     0,
  108,     0,     0,   102,     0,   103,   104,   105,   106,   103,
    0,     0,     0,   108,   105,   108,    16,   107,     0,     0,
   49,    34,    88,   114,     1,     0,     0,    90,    35,     0,
    0,    29,    74,   116,   100,   118,   125,     8,     3,     0,
  125 };

static  K_TYP2    TNext[ ZEMAXTNEXT + 1]  =
{   0,   253,    73,    59,   305,   279,   279,   279,   263,   279,
   25,    43,    79,   299,   298,   141,   142,   143,    21,    25,
  167,   172,   173,   174,    41,    23,   251,   154,   155,   156,
  157,   158,   159,   251,    23,    58,   154,   155,   156,   157,
  158,   159,   302,    22,     5,    12,    39,     8,   251,    14,
  251,   252,    22,    15,   151,    75,    31,    24,    20,   181,
  182,   183,   251,    32,    33,    34,     6,   279,     7,   144,
  145,   146,   147,   148,   149,    70,     9,   152,   153,    16,
  252,    17,    18,    72,   179,   188,   279,   279,   279,    19,
   38,    44,    45,   176,   177,   178,    46,    47,    48,   160,
  274,   162,    50,    51,    52,    53,   163,   277,   165,    55,
   41,    60,    61,    64,   168,   169,   170,    68,   171,    69,
  288,   180,   184,   187,   190,   166,    77,   191,    78,   193 };

static  K_TYP1    TCheck[ ZEMAXTCHECK + 1]  =
{   0,     4,    65,    42,    79,    79,    79,    79,    10,    64,
   18,    22,    78,    65,    64,     5,     5,     5,    18,    19,
   78,    56,    56,    56,    21,    18,     1,    18,    18,    18,
   18,    18,    18,     1,    19,    42,    19,    19,    19,    19,
   19,    19,    71,    18,     2,     6,    21,     3,     1,     8,
    1,     2,    19,     9,    11,    71,    19,    18,    18,    77,
   77,    77,     1,    19,    19,    19,     2,    61,     2,     7,
    7,     7,     7,     7,     7,    60,     3,    12,    13,    14,
    2,    15,    16,    61,    61,    68,    68,    68,    68,    17,
   20,    23,    24,    60,    60,    60,    25,    26,    27,    28,
   29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
   40,    43,    45,    46,    47,    48,    49,    53,    54,    55,
   57,    62,    63,    67,    72,    73,    74,    75,    76,    80,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0 };

static  K_TYP1    TZDefault[ ZEANZZST + 1]  =
{   0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
    0,     0,     0,     0,     0,     0,    19,     0,     0,    73,
   42,    73,     0,     0,    73,    78,    78,     0,     0,     0,
   73,    73,    73,    78,     0,     0,     0,    42,    73,    73,
    0,    68,    77,     0,     0,     0,    77,    77,     0,    73,
   77,     0,     0,    78,     0,     0,     0,     0,     0,     0,
    0 };



static  K_TYP1    NtBase[ ZEANZZST + 1]  =
{   0,     0,     0,    32,     0,     6,     0,    22,     0,     0,
   33,     0,     0,     0,     0,     0,     0,     0,     0,    32,
    0,     1,     0,     0,     0,     0,     0,     0,     0,    17,
    0,     0,     0,     0,     0,     0,    69,     0,     0,     0,
   39,     2,     2,     0,    65,    82,    51,     0,     0,     0,
    4,    83,    56,    84,     0,     0,    65,    67,    88,    89,
   59,     0,    59,     0,     0,     0,    59,    59,     0,    76,
   61,    69,     0,    80,     0,     0,     0,    65,     8,     0,
    0 };

static  K_TYP1    NtNext[ ZEMAXNTNEXT + 1]  =
{   0,     1,     4,    81,    82,    83,    84,     3,     2,   110,
   56,   112,    56,    65,    56,    89,   120,   135,    56,    29,
   28,    80,    11,    90,    91,    92,    93,    94,    95,    96,
   30,    97,    89,    40,    42,    98,   113,    49,    27,    26,
   90,    91,    92,    93,    94,    95,    96,    99,    97,    10,
   85,    88,    98,    36,    35,    27,    26,   121,   100,   101,
  136,    63,   137,   102,    13,   119,    67,   103,    86,    86,
   27,    26,    57,   111,   114,    56,   127,   104,   105,   106,
  107,   108,   109,    37,    99,    74,    56,    87,    87,    76,
   56,    54,    62,    66,    66,   100,   101,   123,    66,    66,
  102,   128,    71,   131,   103,   132,   133,    27,    26,   134,
    0,     0,     0,   124,   104,   105,   106,   107,   108,   109,
    0,     0,   115,   116,   122,   125,     0,     0,     0,   129,
  130,     0,     0,     0,     0,     0,     0,     0,   117,     0,
    0,   118,   126 };

static  K_TYP1    LS[ ZEANZPROD + 1 ]  =
{   0,     8,     3,     3,     3,    17,    18,    18,    17,    20,
   20,    20,    20,    20,    20,    20,    20,    23,    25,    22,
   22,    22,    46,    47,    22,    22,    22,    22,    22,    22,
   32,    24,    33,    24,    26,    59,    59,    59,    28,    15,
   45,    45,    48,    57,    49,    58,    50,     9,    24,    34,
   34,    41,    43,    35,    29,    54,    13,    13,     8,     7,
    1,    16,    16,    16,    42,    42,    42,    42,    42,    42,
    2,     4,     5,     6,    38,    38,    39,    39,    39,    39,
   19,    30,    36,    21,    51,    55,    10,    10,    31,    27,
   19,    21,    11,    11,    11,    24,    43,    43,    43,    56,
   40,    44,    44,    44,    14,    14,    53,    57,    58,    37,
   56,    37,    52,    12 };

static  K_TYP1    LaengeRS[ ZEANZPROD + 1 ]  =
{   0,     2,     1,     1,     1,     1,     1,     1,     2,     1,
    1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
    1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
    2,     3,     2,     3,     3,     1,     1,     1,     3,     3,
    3,     3,     3,     1,     3,     1,     3,     2,     4,     2,
    2,     2,     2,     5,     7,     1,     1,     1,     0,     1,
    1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
    2,     3,     3,     3,     1,     1,     1,     1,     1,     1,
    2,     1,     6,     2,     1,     6,     1,     1,     3,     3,
    3,     3,     1,     1,     1,     3,     1,     1,     1,     2,
    2,     1,     1,     1,     2,     1,     1,     2,     2,     0,
    3,     2,     1,     6 };

static  K_TYP1    FSymbol[ ZEANZZST + 1 ]  =
{   0,    12,    19,    48,     1,    16,    21,    42,    20,    20,
    1,    13,    13,    13,    21,    21,    22,    22,    28,    32,
   26,     2,    11,    11,    11,    11,    11,    11,    13,    23,
   23,    11,    11,    11,    11,    13,    23,    23,    59,     9,
    3,     9,     3,     9,     9,     9,     9,     9,     9,    13,
    9,     9,     9,     9,    13,    11,     7,    13,     9,     9,
   46,    33,    53,     8,    13,    13,    53,    53,    51,     9,
   53,    13,    50,     9,    26,     9,     3,    53,     9,     4,
    4 };

static  K_TYP1    RSymbol[ ZEANZZST + 1 ]  =
{   0,    12,    19,    48,     1,    16,    21,    42,    20,    20,
    1,    13,    13,    13,    21,    21,    22,    22,    28,    32,
   26,     2,    11,    11,    11,    11,    11,    11,    13,    23,
   23,    11,    11,    11,    11,    13,    23,    23,    59,     9,
    3,     9,     3,     9,     9,     9,     9,     9,     9,    13,
    9,     9,     9,     9,    13,    11,     7,    13,     9,     9,
   46,    33,    53,     8,    13,    13,    53,    53,    51,     9,
   53,    13,    50,     9,    26,     9,     3,    53,     9,     4,
    4 };

static  M_TYP    SemKlammer[ ZETINDEX + 1 ]  =
{0X2   ,  0X0   ,  0X0   ,  0X0    };

static  M_TYP    Ueberlesen[ ZETINDEX + 1 ]  =
{0X0   ,  0X0   ,  0X0   ,  0X0    };

