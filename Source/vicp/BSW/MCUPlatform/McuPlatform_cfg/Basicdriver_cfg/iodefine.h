/********************************************************************************/
/*                                                                              */
/* Device     : RH/RH850G3K/R7F701035xAFP                                       */
/* File Name  : iodefine.h                                                      */
/* Abstract   : Definition of I/O Register                                      */
/* History    : V1.00  [Device File version]                                    */
/* This is a typical example.                                                   */
/*                                                                              */
/* Copyright(c) 2013 Renesas Electronics Corp. All rights reserved.             */
/*                                                                              */
/********************************************************************************/
#ifndef __R7F701035xAFPIODEFINE_HEADER__
#define __R7F701035xAFPIODEFINE_HEADER__

typedef struct
{
    unsigned char bit00:1;
    unsigned char bit01:1;
    unsigned char bit02:1;
    unsigned char bit03:1;
    unsigned char bit04:1;
    unsigned char bit05:1;
    unsigned char bit06:1;
    unsigned char bit07:1;
} bitf_T;

struct st_riic0
{                                                          /* RIIC0            */
    union                                                  /*                  */
    {                                                      /* CR1              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } CR1;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* CR2              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } CR2;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* MR1              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } MR1;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* MR2              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } MR2;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* MR3              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } MR3;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* FER              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } FER;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* SER              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } SER;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* IER              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } IER;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* SR1              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
        struct                                             /*                  */
        {                                                  /*  Bit Access      */
            unsigned char  AAS0:1;                         /*   AAS0           */
            unsigned char  AAS1:1;                         /*   AAS1           */
            unsigned char  AAS2:1;                         /*   AAS2           */
            unsigned char  GCA:1;                          /*   GCA            */
            unsigned char  :1;                             /*   Reserved Bits  */
            unsigned char  DID:1;                          /*   DID            */
            unsigned char  :1;                             /*   Reserved Bits  */
            unsigned char  HOA:1;                          /*   HOA            */
            unsigned char  :8;                             /*   Reserved Bits  */
            unsigned char  :8;                             /*   Reserved Bits  */
            unsigned char  :8;                             /*   Reserved Bits  */
        } BIT;                                             /*                  */
    } SR1;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* SR2              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
        struct                                             /*                  */
        {                                                  /*  Bit Access      */
            unsigned char  TMOF:1;                         /*   TMOF           */
            unsigned char  AL:1;                           /*   AL             */
            unsigned char  START:1;                        /*   START          */
            unsigned char  STOP:1;                         /*   STOP           */
            unsigned char  NACKF:1;                        /*   NACKF          */
            unsigned char  RDRF:1;                         /*   RDRF           */
            unsigned char  TEND:1;                         /*   TEND           */
            unsigned char  TDRE:1;                         /*   TDRE           */
            unsigned char  :8;                             /*   Reserved Bits  */
            unsigned char  :8;                             /*   Reserved Bits  */
            unsigned char  :8;                             /*   Reserved Bits  */
        } BIT;                                             /*                  */
    } SR2;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* SAR0             */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } SAR0;                                                /*                  */
    
    union                                                  /*                  */
    {                                                      /* SAR1             */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } SAR1;                                                /*                  */
    
    union                                                  /*                  */
    {                                                      /* SAR2             */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } SAR2;                                                /*                  */
    
    union                                                  /*                  */
    {                                                      /* BRL              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } BRL;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* BRH              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } BRH;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* DRT              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } DRT;                                                 /*                  */
    
    union                                                  /*                  */
    {                                                      /* DRR              */
        unsigned long  UINT32;                             /*  32-bit Access   */
        unsigned short UINT16[2];                          /*  16-bit Access   */
        unsigned char  UINT8[4];                           /*  8-bit Access    */
    } DRR;                                                 /*                  */
    
};

struct st_taud0
{                                                          /* TAUD0            */
    unsigned short CDR0;                                   /*  CDR0            */
    unsigned char  dummy142[2];                            /*                  */
    unsigned short CDR1;                                   /*  CDR1            */
    unsigned char  dummy143[2];                            /*                  */
    unsigned short CDR2;                                   /*  CDR2            */
    unsigned char  dummy144[2];                            /*                  */
    unsigned short CDR3;                                   /*  CDR3            */
    unsigned char  dummy145[2];                            /*                  */
    unsigned short CDR4;                                   /*  CDR4            */
    unsigned char  dummy146[2];                            /*                  */
    unsigned short CDR5;                                   /*  CDR5            */
    unsigned char  dummy147[2];                            /*                  */
    unsigned short CDR6;                                   /*  CDR6            */
    unsigned char  dummy148[2];                            /*                  */
    unsigned short CDR7;                                   /*  CDR7            */
    unsigned char  dummy149[2];                            /*                  */
    unsigned short CDR8;                                   /*  CDR8            */
    unsigned char  dummy150[2];                            /*                  */
    unsigned short CDR9;                                   /*  CDR9            */
    unsigned char  dummy151[2];                            /*                  */
    unsigned short CDR10;                                  /*  CDR10           */
    unsigned char  dummy152[2];                            /*                  */
    unsigned short CDR11;                                  /*  CDR11           */
    unsigned char  dummy153[2];                            /*                  */
    unsigned short CDR12;                                  /*  CDR12           */
    unsigned char  dummy154[2];                            /*                  */
    unsigned short CDR13;                                  /*  CDR13           */
    unsigned char  dummy155[2];                            /*                  */
    unsigned short CDR14;                                  /*  CDR14           */
    unsigned char  dummy156[2];                            /*                  */
    unsigned short CDR15;                                  /*  CDR15           */
    unsigned char  dummy157[2];                            /*                  */
    unsigned short TOL;                                    /*  TOL             */
    unsigned char  dummy158[2];                            /*                  */
    unsigned short RDT;                                    /*  RDT             */
    unsigned char  dummy159[2];                            /*                  */
    unsigned short RSF;                                    /*  RSF             */
    unsigned char  dummy160[2];                            /*                  */
    unsigned short TRO;                                    /*  TRO             */
    unsigned char  dummy161[2];                            /*                  */
    unsigned short TME;                                    /*  TME             */
    unsigned char  dummy162[2];                            /*                  */
    unsigned short TDL;                                    /*  TDL             */
    unsigned char  dummy163[2];                            /*                  */
    unsigned short TO;                                     /*  TO              */
    unsigned char  dummy164[2];                            /*                  */
    unsigned short TOE;                                    /*  TOE             */
    unsigned char  dummy165[34];                           /*                  */
    unsigned short CNT0;                                   /*  CNT0            */
    unsigned char  dummy166[2];                            /*                  */
    unsigned short CNT1;                                   /*  CNT1            */
    unsigned char  dummy167[2];                            /*                  */
    unsigned short CNT2;                                   /*  CNT2            */
    unsigned char  dummy168[2];                            /*                  */
    unsigned short CNT3;                                   /*  CNT3            */
    unsigned char  dummy169[2];                            /*                  */
    unsigned short CNT4;                                   /*  CNT4            */
    unsigned char  dummy170[2];                            /*                  */
    unsigned short CNT5;                                   /*  CNT5            */
    unsigned char  dummy171[2];                            /*                  */
    unsigned short CNT6;                                   /*  CNT6            */
    unsigned char  dummy172[2];                            /*                  */
    unsigned short CNT7;                                   /*  CNT7            */
    unsigned char  dummy173[2];                            /*                  */
    unsigned short CNT8;                                   /*  CNT8            */
    unsigned char  dummy174[2];                            /*                  */
    unsigned short CNT9;                                   /*  CNT9            */
    unsigned char  dummy175[2];                            /*                  */
    unsigned short CNT10;                                  /*  CNT10           */
    unsigned char  dummy176[2];                            /*                  */
    unsigned short CNT11;                                  /*  CNT11           */
    unsigned char  dummy177[2];                            /*                  */
    unsigned short CNT12;                                  /*  CNT12           */
    unsigned char  dummy178[2];                            /*                  */
    unsigned short CNT13;                                  /*  CNT13           */
    unsigned char  dummy179[2];                            /*                  */
    unsigned short CNT14;                                  /*  CNT14           */
    unsigned char  dummy180[2];                            /*                  */
    unsigned short CNT15;                                  /*  CNT15           */
    unsigned char  dummy181[2];                            /*                  */
    unsigned char  CMUR0;                                  /*  CMUR0           */
    unsigned char  dummy182[3];                            /*                  */
    unsigned char  CMUR1;                                  /*  CMUR1           */
    unsigned char  dummy183[3];                            /*                  */
    unsigned char  CMUR2;                                  /*  CMUR2           */
    unsigned char  dummy184[3];                            /*                  */
    unsigned char  CMUR3;                                  /*  CMUR3           */
    unsigned char  dummy185[3];                            /*                  */
    unsigned char  CMUR4;                                  /*  CMUR4           */
    unsigned char  dummy186[3];                            /*                  */
    unsigned char  CMUR5;                                  /*  CMUR5           */
    unsigned char  dummy187[3];                            /*                  */
    unsigned char  CMUR6;                                  /*  CMUR6           */
    unsigned char  dummy188[3];                            /*                  */
    unsigned char  CMUR7;                                  /*  CMUR7           */
    unsigned char  dummy189[3];                            /*                  */
    unsigned char  CMUR8;                                  /*  CMUR8           */
    unsigned char  dummy190[3];                            /*                  */
    unsigned char  CMUR9;                                  /*  CMUR9           */
    unsigned char  dummy191[3];                            /*                  */
    unsigned char  CMUR10;                                 /*  CMUR10          */
    unsigned char  dummy192[3];                            /*                  */
    unsigned char  CMUR11;                                 /*  CMUR11          */
    unsigned char  dummy193[3];                            /*                  */
    unsigned char  CMUR12;                                 /*  CMUR12          */
    unsigned char  dummy194[3];                            /*                  */
    unsigned char  CMUR13;                                 /*  CMUR13          */
    unsigned char  dummy195[3];                            /*                  */
    unsigned char  CMUR14;                                 /*  CMUR14          */
    unsigned char  dummy196[3];                            /*                  */
    unsigned char  CMUR15;                                 /*  CMUR15          */
    unsigned char  dummy197[67];                           /*                  */
    unsigned char  CSR0;                                   /*  CSR0            */
    unsigned char  dummy198[3];                            /*                  */
    unsigned char  CSR1;                                   /*  CSR1            */
    unsigned char  dummy199[3];                            /*                  */
    unsigned char  CSR2;                                   /*  CSR2            */
    unsigned char  dummy200[3];                            /*                  */
    unsigned char  CSR3;                                   /*  CSR3            */
    unsigned char  dummy201[3];                            /*                  */
    unsigned char  CSR4;                                   /*  CSR4            */
    unsigned char  dummy202[3];                            /*                  */
    unsigned char  CSR5;                                   /*  CSR5            */
    unsigned char  dummy203[3];                            /*                  */
    unsigned char  CSR6;                                   /*  CSR6            */
    unsigned char  dummy204[3];                            /*                  */
    unsigned char  CSR7;                                   /*  CSR7            */
    unsigned char  dummy205[3];                            /*                  */
    unsigned char  CSR8;                                   /*  CSR8            */
    unsigned char  dummy206[3];                            /*                  */
    unsigned char  CSR9;                                   /*  CSR9            */
    unsigned char  dummy207[3];                            /*                  */
    unsigned char  CSR10;                                  /*  CSR10           */
    unsigned char  dummy208[3];                            /*                  */
    unsigned char  CSR11;                                  /*  CSR11           */
    unsigned char  dummy209[3];                            /*                  */
    unsigned char  CSR12;                                  /*  CSR12           */
    unsigned char  dummy210[3];                            /*                  */
    unsigned char  CSR13;                                  /*  CSR13           */
    unsigned char  dummy211[3];                            /*                  */
    unsigned char  CSR14;                                  /*  CSR14           */
    unsigned char  dummy212[3];                            /*                  */
    unsigned char  CSR15;                                  /*  CSR15           */
    unsigned char  dummy213[3];                            /*                  */
    unsigned char  CSC0;                                   /*  CSC0            */
    unsigned char  dummy214[3];                            /*                  */
    unsigned char  CSC1;                                   /*  CSC1            */
    unsigned char  dummy215[3];                            /*                  */
    unsigned char  CSC2;                                   /*  CSC2            */
    unsigned char  dummy216[3];                            /*                  */
    unsigned char  CSC3;                                   /*  CSC3            */
    unsigned char  dummy217[3];                            /*                  */
    unsigned char  CSC4;                                   /*  CSC4            */
    unsigned char  dummy218[3];                            /*                  */
    unsigned char  CSC5;                                   /*  CSC5            */
    unsigned char  dummy219[3];                            /*                  */
    unsigned char  CSC6;                                   /*  CSC6            */
    unsigned char  dummy220[3];                            /*                  */
    unsigned char  CSC7;                                   /*  CSC7            */
    unsigned char  dummy221[3];                            /*                  */
    unsigned char  CSC8;                                   /*  CSC8            */
    unsigned char  dummy222[3];                            /*                  */
    unsigned char  CSC9;                                   /*  CSC9            */
    unsigned char  dummy223[3];                            /*                  */
    unsigned char  CSC10;                                  /*  CSC10           */
    unsigned char  dummy224[3];                            /*                  */
    unsigned char  CSC11;                                  /*  CSC11           */
    unsigned char  dummy225[3];                            /*                  */
    unsigned char  CSC12;                                  /*  CSC12           */
    unsigned char  dummy226[3];                            /*                  */
    unsigned char  CSC13;                                  /*  CSC13           */
    unsigned char  dummy227[3];                            /*                  */
    unsigned char  CSC14;                                  /*  CSC14           */
    unsigned char  dummy228[3];                            /*                  */
    unsigned char  CSC15;                                  /*  CSC15           */
    unsigned char  dummy229[3];                            /*                  */
    unsigned short TE;                                     /*  TE              */
    unsigned char  dummy230[2];                            /*                  */
    unsigned short TS;                                     /*  TS              */
    unsigned char  dummy231[2];                            /*                  */
    unsigned short TT;                                     /*  TT              */
    unsigned char  dummy232[54];                           /*                  */
    unsigned short CMOR0;                                  /*  CMOR0           */
    unsigned char  dummy233[2];                            /*                  */
    unsigned short CMOR1;                                  /*  CMOR1           */
    unsigned char  dummy234[2];                            /*                  */
    unsigned short CMOR2;                                  /*  CMOR2           */
    unsigned char  dummy235[2];                            /*                  */
    unsigned short CMOR3;                                  /*  CMOR3           */
    unsigned char  dummy236[2];                            /*                  */
    unsigned short CMOR4;                                  /*  CMOR4           */
    unsigned char  dummy237[2];                            /*                  */
    unsigned short CMOR5;                                  /*  CMOR5           */
    unsigned char  dummy238[2];                            /*                  */
    unsigned short CMOR6;                                  /*  CMOR6           */
    unsigned char  dummy239[2];                            /*                  */
    unsigned short CMOR7;                                  /*  CMOR7           */
    unsigned char  dummy240[2];                            /*                  */
    unsigned short CMOR8;                                  /*  CMOR8           */
    unsigned char  dummy241[2];                            /*                  */
    unsigned short CMOR9;                                  /*  CMOR9           */
    unsigned char  dummy242[2];                            /*                  */
    unsigned short CMOR10;                                 /*  CMOR10          */
    unsigned char  dummy243[2];                            /*                  */
    unsigned short CMOR11;                                 /*  CMOR11          */
    unsigned char  dummy244[2];                            /*                  */
    unsigned short CMOR12;                                 /*  CMOR12          */
    unsigned char  dummy245[2];                            /*                  */
    unsigned short CMOR13;                                 /*  CMOR13          */
    unsigned char  dummy246[2];                            /*                  */
    unsigned short CMOR14;                                 /*  CMOR14          */
    unsigned char  dummy247[2];                            /*                  */
    unsigned short CMOR15;                                 /*  CMOR15          */
    unsigned char  dummy248[2];                            /*                  */
    unsigned short TPS;                                    /*  TPS             */
    unsigned char  dummy249[2];                            /*                  */
    unsigned char  BRS;                                    /*  BRS             */
    unsigned char  dummy250[3];                            /*                  */
    unsigned short TOM;                                    /*  TOM             */
    unsigned char  dummy251[2];                            /*                  */
    unsigned short TOC;                                    /*  TOC             */
    unsigned char  dummy252[2];                            /*                  */
    unsigned short TDE;                                    /*  TDE             */
    unsigned char  dummy253[2];                            /*                  */
    unsigned short TDM;                                    /*  TDM             */
    unsigned char  dummy254[2];                            /*                  */
    unsigned short TRE;                                    /*  TRE             */
    unsigned char  dummy255[2];                            /*                  */
    unsigned short TRC;                                    /*  TRC             */
    unsigned char  dummy256[2];                            /*                  */
    unsigned short RDE;                                    /*  RDE             */
    unsigned char  dummy257[2];                            /*                  */
    unsigned short RDM;                                    /*  RDM             */
    unsigned char  dummy258[2];                            /*                  */
    unsigned short RDS;                                    /*  RDS             */
    unsigned char  dummy259[2];                            /*                  */
    unsigned short RDC;                                    /*  RDC             */
    unsigned char  dummy260[34];                           /*                  */
    unsigned char  EMU;                                    /*  EMU             */
};

struct st_taub0
{                                                          /* TAUB0            */
    unsigned short CDR0;                                   /*  CDR0            */
    unsigned char  dummy261[2];                            /*                  */
    unsigned short CDR1;                                   /*  CDR1            */
    unsigned char  dummy262[2];                            /*                  */
    unsigned short CDR2;                                   /*  CDR2            */
    unsigned char  dummy263[2];                            /*                  */
    unsigned short CDR3;                                   /*  CDR3            */
    unsigned char  dummy264[2];                            /*                  */
    unsigned short CDR4;                                   /*  CDR4            */
    unsigned char  dummy265[2];                            /*                  */
    unsigned short CDR5;                                   /*  CDR5            */
    unsigned char  dummy266[2];                            /*                  */
    unsigned short CDR6;                                   /*  CDR6            */
    unsigned char  dummy267[2];                            /*                  */
    unsigned short CDR7;                                   /*  CDR7            */
    unsigned char  dummy268[2];                            /*                  */
    unsigned short CDR8;                                   /*  CDR8            */
    unsigned char  dummy269[2];                            /*                  */
    unsigned short CDR9;                                   /*  CDR9            */
    unsigned char  dummy270[2];                            /*                  */
    unsigned short CDR10;                                  /*  CDR10           */
    unsigned char  dummy271[2];                            /*                  */
    unsigned short CDR11;                                  /*  CDR11           */
    unsigned char  dummy272[2];                            /*                  */
    unsigned short CDR12;                                  /*  CDR12           */
    unsigned char  dummy273[2];                            /*                  */
    unsigned short CDR13;                                  /*  CDR13           */
    unsigned char  dummy274[2];                            /*                  */
    unsigned short CDR14;                                  /*  CDR14           */
    unsigned char  dummy275[2];                            /*                  */
    unsigned short CDR15;                                  /*  CDR15           */
    unsigned char  dummy276[2];                            /*                  */
    unsigned short TOL;                                    /*  TOL             */
    unsigned char  dummy277[2];                            /*                  */
    unsigned short RDT;                                    /*  RDT             */
    unsigned char  dummy278[2];                            /*                  */
    unsigned short RSF;                                    /*  RSF             */
    unsigned char  dummy279[10];                           /*                  */
    unsigned short TDL;                                    /*  TDL             */
    unsigned char  dummy280[2];                            /*                  */
    unsigned short TO;                                     /*  TO              */
    unsigned char  dummy281[2];                            /*                  */
    unsigned short TOE;                                    /*  TOE             */
    unsigned char  dummy282[34];                           /*                  */
    unsigned short CNT0;                                   /*  CNT0            */
    unsigned char  dummy283[2];                            /*                  */
    unsigned short CNT1;                                   /*  CNT1            */
    unsigned char  dummy284[2];                            /*                  */
    unsigned short CNT2;                                   /*  CNT2            */
    unsigned char  dummy285[2];                            /*                  */
    unsigned short CNT3;                                   /*  CNT3            */
    unsigned char  dummy286[2];                            /*                  */
    unsigned short CNT4;                                   /*  CNT4            */
    unsigned char  dummy287[2];                            /*                  */
    unsigned short CNT5;                                   /*  CNT5            */
    unsigned char  dummy288[2];                            /*                  */
    unsigned short CNT6;                                   /*  CNT6            */
    unsigned char  dummy289[2];                            /*                  */
    unsigned short CNT7;                                   /*  CNT7            */
    unsigned char  dummy290[2];                            /*                  */
    unsigned short CNT8;                                   /*  CNT8            */
    unsigned char  dummy291[2];                            /*                  */
    unsigned short CNT9;                                   /*  CNT9            */
    unsigned char  dummy292[2];                            /*                  */
    unsigned short CNT10;                                  /*  CNT10           */
    unsigned char  dummy293[2];                            /*                  */
    unsigned short CNT11;                                  /*  CNT11           */
    unsigned char  dummy294[2];                            /*                  */
    unsigned short CNT12;                                  /*  CNT12           */
    unsigned char  dummy295[2];                            /*                  */
    unsigned short CNT13;                                  /*  CNT13           */
    unsigned char  dummy296[2];                            /*                  */
    unsigned short CNT14;                                  /*  CNT14           */
    unsigned char  dummy297[2];                            /*                  */
    unsigned short CNT15;                                  /*  CNT15           */
    unsigned char  dummy298[2];                            /*                  */
    unsigned char  CMUR0;                                  /*  CMUR0           */
    unsigned char  dummy299[3];                            /*                  */
    unsigned char  CMUR1;                                  /*  CMUR1           */
    unsigned char  dummy300[3];                            /*                  */
    unsigned char  CMUR2;                                  /*  CMUR2           */
    unsigned char  dummy301[3];                            /*                  */
    unsigned char  CMUR3;                                  /*  CMUR3           */
    unsigned char  dummy302[3];                            /*                  */
    unsigned char  CMUR4;                                  /*  CMUR4           */
    unsigned char  dummy303[3];                            /*                  */
    unsigned char  CMUR5;                                  /*  CMUR5           */
    unsigned char  dummy304[3];                            /*                  */
    unsigned char  CMUR6;                                  /*  CMUR6           */
    unsigned char  dummy305[3];                            /*                  */
    unsigned char  CMUR7;                                  /*  CMUR7           */
    unsigned char  dummy306[3];                            /*                  */
    unsigned char  CMUR8;                                  /*  CMUR8           */
    unsigned char  dummy307[3];                            /*                  */
    unsigned char  CMUR9;                                  /*  CMUR9           */
    unsigned char  dummy308[3];                            /*                  */
    unsigned char  CMUR10;                                 /*  CMUR10          */
    unsigned char  dummy309[3];                            /*                  */
    unsigned char  CMUR11;                                 /*  CMUR11          */
    unsigned char  dummy310[3];                            /*                  */
    unsigned char  CMUR12;                                 /*  CMUR12          */
    unsigned char  dummy311[3];                            /*                  */
    unsigned char  CMUR13;                                 /*  CMUR13          */
    unsigned char  dummy312[3];                            /*                  */
    unsigned char  CMUR14;                                 /*  CMUR14          */
    unsigned char  dummy313[3];                            /*                  */
    unsigned char  CMUR15;                                 /*  CMUR15          */
    unsigned char  dummy314[67];                           /*                  */
    unsigned char  CSR0;                                   /*  CSR0            */
    unsigned char  dummy315[3];                            /*                  */
    unsigned char  CSR1;                                   /*  CSR1            */
    unsigned char  dummy316[3];                            /*                  */
    unsigned char  CSR2;                                   /*  CSR2            */
    unsigned char  dummy317[3];                            /*                  */
    unsigned char  CSR3;                                   /*  CSR3            */
    unsigned char  dummy318[3];                            /*                  */
    unsigned char  CSR4;                                   /*  CSR4            */
    unsigned char  dummy319[3];                            /*                  */
    unsigned char  CSR5;                                   /*  CSR5            */
    unsigned char  dummy320[3];                            /*                  */
    unsigned char  CSR6;                                   /*  CSR6            */
    unsigned char  dummy321[3];                            /*                  */
    unsigned char  CSR7;                                   /*  CSR7            */
    unsigned char  dummy322[3];                            /*                  */
    unsigned char  CSR8;                                   /*  CSR8            */
    unsigned char  dummy323[3];                            /*                  */
    unsigned char  CSR9;                                   /*  CSR9            */
    unsigned char  dummy324[3];                            /*                  */
    unsigned char  CSR10;                                  /*  CSR10           */
    unsigned char  dummy325[3];                            /*                  */
    unsigned char  CSR11;                                  /*  CSR11           */
    unsigned char  dummy326[3];                            /*                  */
    unsigned char  CSR12;                                  /*  CSR12           */
    unsigned char  dummy327[3];                            /*                  */
    unsigned char  CSR13;                                  /*  CSR13           */
    unsigned char  dummy328[3];                            /*                  */
    unsigned char  CSR14;                                  /*  CSR14           */
    unsigned char  dummy329[3];                            /*                  */
    unsigned char  CSR15;                                  /*  CSR15           */
    unsigned char  dummy330[3];                            /*                  */
    unsigned char  CSC0;                                   /*  CSC0            */
    unsigned char  dummy331[3];                            /*                  */
    unsigned char  CSC1;                                   /*  CSC1            */
    unsigned char  dummy332[3];                            /*                  */
    unsigned char  CSC2;                                   /*  CSC2            */
    unsigned char  dummy333[3];                            /*                  */
    unsigned char  CSC3;                                   /*  CSC3            */
    unsigned char  dummy334[3];                            /*                  */
    unsigned char  CSC4;                                   /*  CSC4            */
    unsigned char  dummy335[3];                            /*                  */
    unsigned char  CSC5;                                   /*  CSC5            */
    unsigned char  dummy336[3];                            /*                  */
    unsigned char  CSC6;                                   /*  CSC6            */
    unsigned char  dummy337[3];                            /*                  */
    unsigned char  CSC7;                                   /*  CSC7            */
    unsigned char  dummy338[3];                            /*                  */
    unsigned char  CSC8;                                   /*  CSC8            */
    unsigned char  dummy339[3];                            /*                  */
    unsigned char  CSC9;                                   /*  CSC9            */
    unsigned char  dummy340[3];                            /*                  */
    unsigned char  CSC10;                                  /*  CSC10           */
    unsigned char  dummy341[3];                            /*                  */
    unsigned char  CSC11;                                  /*  CSC11           */
    unsigned char  dummy342[3];                            /*                  */
    unsigned char  CSC12;                                  /*  CSC12           */
    unsigned char  dummy343[3];                            /*                  */
    unsigned char  CSC13;                                  /*  CSC13           */
    unsigned char  dummy344[3];                            /*                  */
    unsigned char  CSC14;                                  /*  CSC14           */
    unsigned char  dummy345[3];                            /*                  */
    unsigned char  CSC15;                                  /*  CSC15           */
    unsigned char  dummy346[3];                            /*                  */
    unsigned short TE;                                     /*  TE              */
    unsigned char  dummy347[2];                            /*                  */
    unsigned short TS;                                     /*  TS              */
    unsigned char  dummy348[2];                            /*                  */
    unsigned short TT;                                     /*  TT              */
    unsigned char  dummy349[54];                           /*                  */
    unsigned short CMOR0;                                  /*  CMOR0           */
    unsigned char  dummy350[2];                            /*                  */
    unsigned short CMOR1;                                  /*  CMOR1           */
    unsigned char  dummy351[2];                            /*                  */
    unsigned short CMOR2;                                  /*  CMOR2           */
    unsigned char  dummy352[2];                            /*                  */
    unsigned short CMOR3;                                  /*  CMOR3           */
    unsigned char  dummy353[2];                            /*                  */
    unsigned short CMOR4;                                  /*  CMOR4           */
    unsigned char  dummy354[2];                            /*                  */
    unsigned short CMOR5;                                  /*  CMOR5           */
    unsigned char  dummy355[2];                            /*                  */
    unsigned short CMOR6;                                  /*  CMOR6           */
    unsigned char  dummy356[2];                            /*                  */
    unsigned short CMOR7;                                  /*  CMOR7           */
    unsigned char  dummy357[2];                            /*                  */
    unsigned short CMOR8;                                  /*  CMOR8           */
    unsigned char  dummy358[2];                            /*                  */
    unsigned short CMOR9;                                  /*  CMOR9           */
    unsigned char  dummy359[2];                            /*                  */
    unsigned short CMOR10;                                 /*  CMOR10          */
    unsigned char  dummy360[2];                            /*                  */
    unsigned short CMOR11;                                 /*  CMOR11          */
    unsigned char  dummy361[2];                            /*                  */
    unsigned short CMOR12;                                 /*  CMOR12          */
    unsigned char  dummy362[2];                            /*                  */
    unsigned short CMOR13;                                 /*  CMOR13          */
    unsigned char  dummy363[2];                            /*                  */
    unsigned short CMOR14;                                 /*  CMOR14          */
    unsigned char  dummy364[2];                            /*                  */
    unsigned short CMOR15;                                 /*  CMOR15          */
    unsigned char  dummy365[2];                            /*                  */
    unsigned short TPS;                                    /*  TPS             */
    unsigned char  dummy366[6];                            /*                  */
    unsigned short TOM;                                    /*  TOM             */
    unsigned char  dummy367[2];                            /*                  */
    unsigned short TOC;                                    /*  TOC             */
    unsigned char  dummy368[2];                            /*                  */
    unsigned short TDE;                                    /*  TDE             */
    unsigned char  dummy369[14];                           /*                  */
    unsigned short RDE;                                    /*  RDE             */
    unsigned char  dummy370[2];                            /*                  */
    unsigned short RDM;                                    /*  RDM             */
    unsigned char  dummy371[2];                            /*                  */
    unsigned short RDS;                                    /*  RDS             */
    unsigned char  dummy372[2];                            /*                  */
    unsigned short RDC;                                    /*  RDC             */
    unsigned char  dummy373[34];                           /*                  */
    unsigned char  EMU;                                    /*  EMU             */
};

struct st_tauj0
{                                                          /* TAUJ0            */
    unsigned long  CDR0;                                   /*  CDR0            */
    unsigned long  CDR1;                                   /*  CDR1            */
    unsigned long  CDR2;                                   /*  CDR2            */
    unsigned long  CDR3;                                   /*  CDR3            */
    unsigned long  CNT0;                                   /*  CNT0            */
    unsigned long  CNT1;                                   /*  CNT1            */
    unsigned long  CNT2;                                   /*  CNT2            */
    unsigned long  CNT3;                                   /*  CNT3            */
    unsigned char  CMUR0;                                  /*  CMUR0           */
    unsigned char  dummy487[3];                            /*                  */
    unsigned char  CMUR1;                                  /*  CMUR1           */
    unsigned char  dummy488[3];                            /*                  */
    unsigned char  CMUR2;                                  /*  CMUR2           */
    unsigned char  dummy489[3];                            /*                  */
    unsigned char  CMUR3;                                  /*  CMUR3           */
    unsigned char  dummy490[3];                            /*                  */
    unsigned char  CSR0;                                   /*  CSR0            */
    unsigned char  dummy491[3];                            /*                  */
    unsigned char  CSR1;                                   /*  CSR1            */
    unsigned char  dummy492[3];                            /*                  */
    unsigned char  CSR2;                                   /*  CSR2            */
    unsigned char  dummy493[3];                            /*                  */
    unsigned char  CSR3;                                   /*  CSR3            */
    unsigned char  dummy494[3];                            /*                  */
    unsigned char  CSC0;                                   /*  CSC0            */
    unsigned char  dummy495[3];                            /*                  */
    unsigned char  CSC1;                                   /*  CSC1            */
    unsigned char  dummy496[3];                            /*                  */
    unsigned char  CSC2;                                   /*  CSC2            */
    unsigned char  dummy497[3];                            /*                  */
    unsigned char  CSC3;                                   /*  CSC3            */
    unsigned char  dummy498[3];                            /*                  */
    unsigned char  TE;                                     /*  TE              */
    unsigned char  dummy499[3];                            /*                  */
    unsigned char  TS;                                     /*  TS              */
    unsigned char  dummy500[3];                            /*                  */
    unsigned char  TT;                                     /*  TT              */
    unsigned char  dummy501[3];                            /*                  */
    unsigned char  TO;                                     /*  TO              */
    unsigned char  dummy502[3];                            /*                  */
    unsigned char  TOE;                                    /*  TOE             */
    unsigned char  dummy503[3];                            /*                  */
    unsigned char  TOL;                                    /*  TOL             */
    unsigned char  dummy504[3];                            /*                  */
    unsigned char  RDT;                                    /*  RDT             */
    unsigned char  dummy505[3];                            /*                  */
    unsigned char  RSF;                                    /*  RSF             */
    unsigned char  dummy506[19];                           /*                  */
    unsigned short CMOR0;                                  /*  CMOR0           */
    unsigned char  dummy507[2];                            /*                  */
    unsigned short CMOR1;                                  /*  CMOR1           */
    unsigned char  dummy508[2];                            /*                  */
    unsigned short CMOR2;                                  /*  CMOR2           */
    unsigned char  dummy509[2];                            /*                  */
    unsigned short CMOR3;                                  /*  CMOR3           */
    unsigned char  dummy510[2];                            /*                  */
    unsigned short TPS;                                    /*  TPS             */
    unsigned char  dummy511[2];                            /*                  */
    unsigned char  BRS;                                    /*  BRS             */
    unsigned char  dummy512[3];                            /*                  */
    unsigned char  TOM;                                    /*  TOM             */
    unsigned char  dummy513[3];                            /*                  */
    unsigned char  TOC;                                    /*  TOC             */
    unsigned char  dummy514[3];                            /*                  */
    unsigned char  RDE;                                    /*  RDE             */
    unsigned char  dummy515[3];                            /*                  */
    unsigned char  RDM;                                    /*  RDM             */
    unsigned char  dummy516[3];                            /*                  */
    unsigned char  EMU;                                    /*  EMU             */
};

struct st_tauj1
{                                                          /* TAUJ1            */
    unsigned long  CDR0;                                   /*  CDR0            */
    unsigned long  CDR1;                                   /*  CDR1            */
    unsigned long  CDR2;                                   /*  CDR2            */
    unsigned long  CDR3;                                   /*  CDR3            */
    unsigned long  CNT0;                                   /*  CNT0            */
    unsigned long  CNT1;                                   /*  CNT1            */
    unsigned long  CNT2;                                   /*  CNT2            */
    unsigned long  CNT3;                                   /*  CNT3            */
    unsigned char  CMUR0;                                  /*  CMUR0           */
    unsigned char  dummy517[3];                            /*                  */
    unsigned char  CMUR1;                                  /*  CMUR1           */
    unsigned char  dummy518[3];                            /*                  */
    unsigned char  CMUR2;                                  /*  CMUR2           */
    unsigned char  dummy519[3];                            /*                  */
    unsigned char  CMUR3;                                  /*  CMUR3           */
    unsigned char  dummy520[3];                            /*                  */
    unsigned char  CSR0;                                   /*  CSR0            */
    unsigned char  dummy521[3];                            /*                  */
    unsigned char  CSR1;                                   /*  CSR1            */
    unsigned char  dummy522[3];                            /*                  */
    unsigned char  CSR2;                                   /*  CSR2            */
    unsigned char  dummy523[3];                            /*                  */
    unsigned char  CSR3;                                   /*  CSR3            */
    unsigned char  dummy524[3];                            /*                  */
    unsigned char  CSC0;                                   /*  CSC0            */
    unsigned char  dummy525[3];                            /*                  */
    unsigned char  CSC1;                                   /*  CSC1            */
    unsigned char  dummy526[3];                            /*                  */
    unsigned char  CSC2;                                   /*  CSC2            */
    unsigned char  dummy527[3];                            /*                  */
    unsigned char  CSC3;                                   /*  CSC3            */
    unsigned char  dummy528[3];                            /*                  */
    unsigned char  TE;                                     /*  TE              */
    unsigned char  dummy529[3];                            /*                  */
    unsigned char  TS;                                     /*  TS              */
    unsigned char  dummy530[3];                            /*                  */
    unsigned char  TT;                                     /*  TT              */
    unsigned char  dummy531[3];                            /*                  */
    unsigned char  TO;                                     /*  TO              */
    unsigned char  dummy532[3];                            /*                  */
    unsigned char  TOE;                                    /*  TOE             */
    unsigned char  dummy533[3];                            /*                  */
    unsigned char  TOL;                                    /*  TOL             */
    unsigned char  dummy534[3];                            /*                  */
    unsigned char  RDT;                                    /*  RDT             */
    unsigned char  dummy535[3];                            /*                  */
    unsigned char  RSF;                                    /*  RSF             */
    unsigned char  dummy536[19];                           /*                  */
    unsigned short CMOR0;                                  /*  CMOR0           */
    unsigned char  dummy537[2];                            /*                  */
    unsigned short CMOR1;                                  /*  CMOR1           */
    unsigned char  dummy538[2];                            /*                  */
    unsigned short CMOR2;                                  /*  CMOR2           */
    unsigned char  dummy539[2];                            /*                  */
    unsigned short CMOR3;                                  /*  CMOR3           */
    unsigned char  dummy540[2];                            /*                  */
    unsigned short TPS;                                    /*  TPS             */
    unsigned char  dummy541[2];                            /*                  */
    unsigned char  BRS;                                    /*  BRS             */
    unsigned char  dummy542[3];                            /*                  */
    unsigned char  TOM;                                    /*  TOM             */
    unsigned char  dummy543[3];                            /*                  */
    unsigned char  TOC;                                    /*  TOC             */
    unsigned char  dummy544[3];                            /*                  */
    unsigned char  RDE;                                    /*  RDE             */
    unsigned char  dummy545[3];                            /*                  */
    unsigned char  RDM;                                    /*  RDM             */
    unsigned char  dummy546[3];                            /*                  */
    unsigned char  EMU;                                    /*  EMU             */
};

struct st_wdta0
{                                                          /* WDTA0            */
    unsigned char  WDTE;                                   /*  WDTE            */
    unsigned char  dummy1260[3];                           /*                  */
    unsigned char  EVAC;                                   /*  EVAC            */
    unsigned char  dummy1261[3];                           /*                  */
    unsigned char  REF;                                    /*  REF             */
    unsigned char  dummy1262[3];                           /*                  */
    unsigned char  MD;                                     /*  MD              */
};

#define SELB_INTC1         (*(volatile unsigned short *)0xFFBC0300)
#define SELB_INTC2         (*(volatile unsigned short *)0xFFBC0304)

#define DNFATAUD0ICTL      (*(volatile unsigned char  *)0xFFC30000)
#define DNFATAUD0IEN       (*(volatile unsigned short *)0xFFC30004)
#define DNFATAUB0ICTL      (*(volatile unsigned char  *)0xFFC30020)
#define DNFATAUB0IEN       (*(volatile unsigned short *)0xFFC30024)

#define EEPRDCYCL          (*(volatile unsigned char  *)0xFFC5A010)

#define PROTCMD0           (*(volatile unsigned long  *)0xFFF80000)
#define PROTS0             (*(volatile unsigned long  *)0xFFF80004)

#define WDTNMIF            (*(volatile unsigned long  *)0xFFF80200)
#define WDTNMIFC           (*(volatile unsigned long  *)0xFFF80208)

#define ROSCE              (*(volatile unsigned long  *)0xFFF81000)
#define ROSCS              (*(volatile unsigned long  *)0xFFF81004)
#define ROSCSTPM           (*(volatile unsigned long  *)0xFFF81018)

#define MOSCE              (*(volatile unsigned long  *)0xFFF81100)
#define MOSCS              (*(volatile unsigned long  *)0xFFF81104)
#define MOSCC              (*(volatile unsigned long  *)0xFFF81108)
#define MOSCST             (*(volatile unsigned long  *)0xFFF8110C)
#define MOSCSTPM           (*(volatile unsigned long  *)0xFFF81118)
#define SOSCE              (*(volatile unsigned long  *)0xFFF81200)
#define SOSCS              (*(volatile unsigned long  *)0xFFF81204)
#define SOSCST             (*(volatile unsigned long  *)0xFFF8120C)

#define P0                 (*(volatile unsigned short *)0xFFC10000u)
#define P10                (*(volatile unsigned short *)0xFFC10028u)
#define PM0                (*(volatile unsigned short *)0xFFC10300u)
#define PMC0               (*(volatile unsigned short *)0xFFC10400u)
#define PIPC0              (*(volatile unsigned short *)0xFFC14200u)
#define PFC0               (*(volatile unsigned short *)0xFFC10500u)
#define PFCE0              (*(volatile unsigned short *)0xFFC10600u)
#define PFCAE0             (*(volatile unsigned short *)0xFFC10A00u)

#define CKSC_AWDTAD_CTL    (*(volatile unsigned long  *)0xFFF82000)
#define CKSC_AWDTAD_ACT    (*(volatile unsigned long  *)0xFFF82008)
#define CKSC_AWDTAD_STPM   (*(volatile unsigned long  *)0xFFF82018)
#define CKSC_ATAUJS_CTL    (*(volatile unsigned long  *)0xFFF82100)
#define CKSC_ATAUJS_ACT    (*(volatile unsigned long  *)0xFFF82108)
#define CKSC_ATAUJD_CTL    (*(volatile unsigned long  *)0xFFF82200)
#define CKSC_ATAUJD_ACT    (*(volatile unsigned long  *)0xFFF82208)
#define CKSC_ATAUJD_STPM   (*(volatile unsigned long  *)0xFFF82218)
#define CKSC_ARTCAS_CTL    (*(volatile unsigned long  *)0xFFF82300)
#define CKSC_ARTCAS_ACT    (*(volatile unsigned long  *)0xFFF82308)
#define CKSC_ARTCAD_CTL    (*(volatile unsigned long  *)0xFFF82400)
#define CKSC_ARTCAD_ACT    (*(volatile unsigned long  *)0xFFF82408)
#define CKSC_ARTCAD_STPM   (*(volatile unsigned long  *)0xFFF82418)
#define CKSC_AADCAS_CTL    (*(volatile unsigned long  *)0xFFF82500)
#define CKSC_AADCAS_ACT    (*(volatile unsigned long  *)0xFFF82508)
#define CKSC_AADCAD_CTL    (*(volatile unsigned long  *)0xFFF82600)
#define CKSC_AADCAD_ACT    (*(volatile unsigned long  *)0xFFF82608)
#define CKSC_AADCAD_STPM   (*(volatile unsigned long  *)0xFFF82618)
#define CKSC_AFOUTS_CTL    (*(volatile unsigned long  *)0xFFF82700)
#define CKSC_AFOUTS_ACT    (*(volatile unsigned long  *)0xFFF82708)
#define CKSC_AFOUTS_STPM   (*(volatile unsigned long  *)0xFFF82718)

#define PROTCMD1           (*(volatile unsigned long  *)0xFFF88000)
#define PROTS1             (*(volatile unsigned long  *)0xFFF88004)

#define PLLE               (*(volatile unsigned long  *)0xFFF89000)
#define PLLS               (*(volatile unsigned long  *)0xFFF89004)
#define PLLC               (*(volatile unsigned long  *)0xFFF89008)

#define CKSC_CPUCLKS_CTL   (*(volatile unsigned long  *)0xFFF8A000)
#define CKSC_CPUCLKS_ACT   (*(volatile unsigned long  *)0xFFF8A008)
#define CKSC_CPUCLKD_CTL   (*(volatile unsigned long  *)0xFFF8A100)
#define CKSC_CPUCLKD_ACT   (*(volatile unsigned long  *)0xFFF8A108)
#define CKSC_IPERI1S_CTL   (*(volatile unsigned long  *)0xFFF8A200)
#define CKSC_IPERI1S_ACT   (*(volatile unsigned long  *)0xFFF8A208)
#define CKSC_IPERI2S_CTL   (*(volatile unsigned long  *)0xFFF8A300)
#define CKSC_IPERI2S_ACT   (*(volatile unsigned long  *)0xFFF8A308)
#define CKSC_ILINS_CTL     (*(volatile unsigned long  *)0xFFF8A400)
#define CKSC_ILINS_ACT     (*(volatile unsigned long  *)0xFFF8A408)
#define CKSC_IADCAS_CTL    (*(volatile unsigned long  *)0xFFF8A500)
#define CKSC_IADCAS_ACT    (*(volatile unsigned long  *)0xFFF8A508)
#define CKSC_IADCAD_CTL    (*(volatile unsigned long  *)0xFFF8A600)
#define CKSC_IADCAD_ACT    (*(volatile unsigned long  *)0xFFF8A608)
#define CKSC_ILIND_CTL     (*(volatile unsigned long  *)0xFFF8A800)
#define CKSC_ILIND_ACT     (*(volatile unsigned long  *)0xFFF8A808)
#define CKSC_ILIND_STPM    (*(volatile unsigned long  *)0xFFF8A818)
#define CKSC_ICANS_CTL     (*(volatile unsigned long  *)0xFFF8A900)
#define CKSC_ICANS_ACT     (*(volatile unsigned long  *)0xFFF8A908)
#define CKSC_ICANS_STPM    (*(volatile unsigned long  *)0xFFF8A918)
#define CKSC_ICANOSCD_CTL  (*(volatile unsigned long  *)0xFFF8AA00)
#define CKSC_ICANOSCD_ACT  (*(volatile unsigned long  *)0xFFF8AA08)
#define CKSC_ICANOSCD_STPM (*(volatile unsigned long  *)0xFFF8AA18)
#define CKSC_ICSIS_CTL     (*(volatile unsigned long  *)0xFFF8AB00)
#define CKSC_ICSIS_ACT     (*(volatile unsigned long  *)0xFFF8AB08)

#define RFADCA0ERR         (((volatile bitf_T *)0xFFFFA05F)->bit04)

#define RIIC0   (*(volatile struct st_riic0   *)0xFFCA0000u) /* RIIC0 */

#define TAUD0   (*(volatile struct st_taud0   *)0xFFE20000u) /* TAUD0 */
#define TAUB0   (*(volatile struct st_taub0   *)0xFFE30000u) /* TAUB0 */

#define TAUJ0   (*(volatile struct st_tauj0   *)0xFFE50000u) /* TAUJ0 */
#define TAUJ1   (*(volatile struct st_tauj1   *)0xFFE51000u) /* TAUJ1 */

#define WDTA0   (*(volatile struct st_wdta0   *)0xFFED0000u) /* WDTA0 */

#endif
