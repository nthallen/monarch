/* Date should go here */
#define    ZEMAXTERMINALCODE 24
#define    ZEMAXRSLAENGE     4
#define    ZEANZZST          39
#define    ZEMAXTEINTRAG     187
#define    ZEMAXNTEINTRAG    80
#define    ZEMAXTE1          39
#define    ZEMAXTE2          113
#define    ZEMAXNTE          39
#define    ZEANZNT           41
#define    ZEANZPROD         74
#define    ZEMAXTNEXT        128
#define    ZEMAXTCHECK       149
#define    ZEMAXNTNEXT       270
#define    ZETINDEX          ZEMAXTERMINALCODE / M_BITS
#define    ZESTOPSYMBOL      1
static  K_TYP1    TBase[ ZEANZZST + 1]  =
{   0,    95,    75,     0,    20,     5,     7,    39,     0,    44,
  104,     0,    97,    54,    59,    60,    80,    83,     0,     0,
   63,   102,    69,    75,   107,    22,    86,    95,    21,     0,
  110,     0,   117,   109,   112,    42,   123,    42,   114,   125 };

static  K_TYP1    TNext[ ZEMAXTNEXT + 1]  =
{   0,   156,   178,    92,   178,   178,   178,   178,   178,    36,
  178,   178,   178,   178,   178,    84,   178,   178,   178,     8,
  178,   178,   178,   177,   178,   177,   177,   177,     7,   174,
   31,   177,   177,   177,   177,   177,    83,   177,   177,   177,
  177,   177,   177,   177,   183,   177,   183,   183,   183,   186,
   39,     9,   183,   183,   183,   183,   183,   161,   183,   183,
  183,   110,   183,   183,   183,   134,   183,   134,   134,   134,
   88,    26,    90,   169,   134,   134,   169,   134,    27,   134,
  134,   134,    97,   134,   134,   134,   167,   134,    98,    13,
    4,   167,   167,     6,    14,     8,   167,    89,   167,   175,
  167,   167,   167,    91,     7,    15,    11,   155,    85,    86,
  155,    18,    30,   155,    89,   170,   155,   173,   102,    38,
  173,    19,   181,   179,   106,   108,   111,   187,    94 };

static  K_TYP1    TCheck[ ZEMAXTCHECK + 1]  =
{   0,     3,    29,    11,    29,    29,    29,    29,    29,    29,
   29,    29,    29,    29,    29,     5,    29,    29,    29,     6,
   29,    29,    29,    28,    29,    28,    28,    28,     6,    25,
   25,    28,    28,    28,    28,    28,     4,    28,    28,    28,
   28,    28,    28,    28,    35,    28,    35,    35,    35,    37,
   37,     7,    35,    35,    35,    35,    35,     9,    35,    35,
   35,    35,    35,    35,    35,    20,    35,    20,    20,    20,
   13,    14,    13,    20,    20,    20,    20,    20,    15,    20,
   20,    20,    22,    20,    20,    20,    16,    20,    23,    17,
    2,    16,    16,     2,    17,    17,    16,    16,    16,    26,
   16,    16,    16,    17,    17,    17,    10,     1,    10,    10,
    1,    12,    21,     1,    12,    21,     1,    24,    27,    33,
   24,    12,    33,    30,    32,    34,    36,    38,    39,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0 };

static  K_TYP1    TZDefault[ ZEANZZST + 1]  =
{   0,     0,     6,     0,     0,     0,     0,     0,     9,    10,
   12,     0,    17,     0,     0,     0,     0,    13,    39,    39,
    0,     0,     0,     0,    10,     0,    10,     0,     0,     0,
   10,    39,     0,     0,     0,     0,     0,     0,    10,     0 };



static  K_TYP2    NtBase[ ZEANZZST + 1]  =
{   0,     0,    89,     0,     0,     0,     4,     0,     0,    38,
  104,     0,   222,     1,     0,     0,     2,   251,     0,    11,
    0,     0,     0,     0,   132,     3,   160,     0,     0,    13,
   76,    13,     0,     0,     0,    11,     0,     0,   191,    29 };

static  K_TYP1    NtNext[ ZEMAXNTNEXT + 1]  =
{   0,     1,     3,     0,    44,    45,    46,    47,    48,    49,
   50,    17,    43,    75,    12,    10,    20,    51,     0,    52,
   25,    70,    29,    32,    16,    53,    35,    62,    54,    55,
   56,    57,    71,    29,    37,    29,    76,     2,    78,    21,
   58,    22,    44,    45,    46,    47,    48,    49,    50,    17,
   80,    29,    12,    10,    20,    51,     0,    52,     0,     0,
    0,     0,    16,    53,     0,     0,    54,    55,    56,    57,
    0,     0,     0,     0,     0,     0,     0,    21,    58,    23,
   44,    45,    46,    47,    48,    49,    50,    17,     0,     0,
   12,    10,    20,    51,     0,    52,     0,    40,     0,     0,
   16,    53,     0,     0,    54,    55,    56,    57,    44,    45,
   46,    47,    48,    49,    50,    17,    77,     0,    12,    59,
   60,     0,    24,    52,     5,    41,     0,    42,    16,    53,
    0,     0,    54,    55,    56,    57,    44,    45,    46,    47,
   48,    49,    50,    17,     0,     0,    12,    72,    60,     0,
    0,    52,     0,     0,     0,     0,    16,    53,     0,     0,
   54,    55,    56,    57,    44,    45,    46,    47,    48,    49,
   50,    17,     0,     0,    12,     0,    73,     0,     0,    52,
    0,     0,     0,     0,    16,    53,     0,     0,    54,    55,
   56,    57,    34,    33,    74,    44,    45,    46,    47,    48,
   49,    50,    17,     0,     0,    12,     0,    73,     0,     0,
   52,     0,     0,     0,     0,    16,    53,     0,     0,    54,
   55,    56,    57,     0,     0,    79,    44,    45,    46,    47,
   48,    49,    50,    17,     0,     0,     0,     0,     0,     0,
    0,    52,     0,     0,     0,     0,    16,    53,     0,     0,
   61,    55,    56,    57,    63,    64,    65,    66,    67,    68,
   69,     0,     0,    28,     0,     0,     0,     0,     0,     0,
   52 };

static  K_TYP1    LS[ ZEANZPROD + 1 ]  =
{   0,    38,    37,     2,    36,    28,    28,    28,    28,    28,
   28,    28,    40,     6,    24,    16,    28,    29,    29,    39,
   18,    15,    16,    24,    12,     3,     3,     3,     3,     3,
    3,    30,    31,    18,    34,    33,    10,    21,    39,    26,
   33,    20,    37,     1,    35,    37,    14,    14,    41,    19,
   25,    19,     7,    14,    11,    22,    40,    41,     8,     8,
   17,    20,    32,     9,    26,    21,    41,     4,    32,     5,
   13,    27,    23,    20,    32 };

static  K_TYP1    LaengeRS[ ZEANZPROD + 1 ]  =
{   0,     1,     2,     2,     2,     1,     1,     1,     1,     1,
    1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
    1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
    1,     2,     2,     2,     1,     1,     3,     2,     3,     2,
    3,     4,     0,     1,     2,     3,     1,     1,     0,     1,
    1,     1,     1,     2,     1,     1,     1,     1,     3,     4,
    2,     0,     0,     3,     0,     1,     2,     4,     1,     4,
    1,     1,     2,     2,     2 };

static  K_TYP1    FSymbol[ ZEANZZST + 1 ]  =
{   0,    12,    12,     1,    16,    10,    12,    12,    13,    13,
   20,     3,    20,    16,    12,    18,     6,    20,     3,     3,
   10,    13,    13,    13,    10,     7,    13,    23,     2,     2,
   20,     3,     7,    13,    13,     2,     3,     7,    20,     3 };

static  K_TYP1    RSymbol[ ZEANZZST + 1 ]  =
{   0,    12,    12,     1,    16,    10,    12,    12,    13,    13,
   20,     3,    20,    16,    12,    18,     6,    20,     3,     3,
   10,    13,    13,    13,    10,     7,    13,    23,     2,     2,
   20,     3,     7,    13,    13,     2,     3,     7,    20,     3 };

static  M_TYP    SemKlammer[ ZETINDEX + 1 ]  =
{0X2   ,  0X0    };

static  M_TYP    Ueberlesen[ ZETINDEX + 1 ]  =
{0X0   ,  0X0    };

