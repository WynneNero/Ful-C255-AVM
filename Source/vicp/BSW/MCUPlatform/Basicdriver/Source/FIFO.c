/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Zhang Jiacheng           										   *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*-----------------------------------------------------------------------
* 0.1	   Jun 02,2016                     Initial version
*----------------------------------------------------------------------
* 0.2         Jan 24,2017    ZhangJie     fix Coverity warning.
*----------------------------------------------------------------------
* 0.3         Apr 01,2017    PEI Jingli     Fix include files.
*=====================================================================*/
/**** System include files ****/
#include "Config.h"

/*---Public include files---------------------------------------------*/

/*---Private include files--------------------------------------------*/
#include "FIFO.h"   
#include "FIFO_IF.h" 

/*===VARIABLES========================================================*/

/*---Global-----------------------------------------------------------*/

/*---Private----------------------------------------------------------*/

/*===FUNCTIONS========================================================*/
static BOOL fifo_is_empty(FIFO_TYPE *this  );
static BOOL fifo_is_full(FIFO_TYPE *this  );
static BOOL fifo_input_byte( FIFO_TYPE *this , unsigned char byte );
static BOOL fifo_output_byte(FIFO_TYPE *this, U8 *pdata);
static BOOL fifo_have_enough_space(FIFO_TYPE *this , U8 nBytes);

/*---Global-----------------------------------------------------------*/

/*******************************************************************************
**  FUNCTION      : fifo_init
**  DESCRIPTION   : This function initialize FIFO
**  PARAMETERS    : this
**                  pBuf
**                  nSize
**  RETURN        : void
*******************************************************************************/
void fifo_init( FIFO_TYPE *this, U8 *pBuf, U16 nSize)
{
    this->mpFIFOBuffer = pBuf;
    this->mFIFOHead = 0x00;
    this->mFIFOTail = 0x00;
    this->mFIFOLength = 0x00; /*888 current length*/
    this->mFIFOSize = nSize;
}

/*******************************************************************************
**  FUNCTION      : fifo_input_frame
**  DESCRIPTION   : This function input a frame to fifo buffer
**  PARAMETERS    : this
**                  pFrame
**                  nBytes
**  RETURN        : void
*******************************************************************************/
BOOL fifo_input_frame( FIFO_TYPE *this , U8 *pFrame , U8 length)
{
    U8 i;
    U8 *pTemp = pFrame;
    BOOL bRet = TRUE;

    if (fifo_have_enough_space(this, length))
    {
        if (fifo_input_byte(this, length))
        {
            for (i = 0x00; i < length; i++) /*input (1 +nbyte) byte to FIFO*/
            {
                if (fifo_input_byte(this, *pTemp++))
                {
                    /*do nothing*/
                }
                else
                {
                    bRet = FALSE;
                    continue;
                }
            }
        }
        else
        {
            bRet = FALSE;
        }
    }
    else
    {
        bRet = FALSE;
    }
    return bRet;
}


/*888 improved block input. And #byte is not stored.*/
BOOL fifo_input_block( FIFO_TYPE *this , U8 *pFrame , U8 length) /*888 optimized*/
{
    U16 counter = 0;
    U16 halfone = 0;
    BOOL bRet = TRUE;

    if ((this->mFIFOSize - this->mFIFOLength) >= length) /*have enough space available*/
    {
        if ((this->mFIFOTail + length) < this->mFIFOSize)
        {
            this->mFIFOLength += length;
            for (counter=0; counter<length; counter++)
                this->mpFIFOBuffer[this->mFIFOTail + counter] = pFrame[counter];
            this->mFIFOTail += length;
        }
        else
        {
            this->mFIFOLength += length;
            for (counter=0; (this->mFIFOTail+counter)<this->mFIFOSize; counter++)
                this->mpFIFOBuffer[this->mFIFOTail+counter] = pFrame[counter];
            this->mFIFOTail = 0;
            halfone = counter;
            length = length - (U8)counter;
            for (counter=0; counter<length; counter++)
                this->mpFIFOBuffer[this->mFIFOTail+counter] = pFrame[halfone+counter];
            this->mFIFOTail += length;
        }
    }
    else
    {
        bRet = FALSE;
    }
    return bRet;
}

BOOL fifo_output_block( FIFO_TYPE *this , U8 *pFrame , U8 length) /*888 optimized*/
{
    U16 counter = 0;
    U16 halfone = 0;
    BOOL bRet = TRUE;

    if (this->mFIFOLength >= length) /*fetch more than contained*/
    {
        if ((this->mFIFOHead+ length) < this->mFIFOSize)
        {
            this->mFIFOLength -= length;
            for (counter=0; counter<length; counter++)
                pFrame[counter] = this->mpFIFOBuffer[this->mFIFOHead + counter];
            this->mFIFOHead+= length;
        }
        else
        {
            this->mFIFOLength -= length;
            for (counter=0; (this->mFIFOHead+counter)<this->mFIFOSize; counter++)
                pFrame[counter]= this->mpFIFOBuffer[this->mFIFOHead+counter];
            this->mFIFOHead= 0;
            halfone = counter;
            length = length - (U8)counter;
            for (counter=0; counter<length; counter++)
                pFrame[halfone+counter]= this->mpFIFOBuffer[this->mFIFOHead+counter];
            this->mFIFOHead+= length;
        }
    }
    else 
    {
        bRet = FALSE;
    }
    return bRet;
}


/*******************************************************************************
**  FUNCTION      : fifo_output_frame
**  DESCRIPTION   : This function output a frame from FIFO buffer
**  PARAMETERS    : this
**                  pFrame
**                  nBytes
**  RETURN        : void
*******************************************************************************/
BOOL fifo_output_frame( FIFO_TYPE *this, U8 *pFrame, U8 *pLength)
{
    U8 i;
    U8 tempVal;
    U16 tempLength;
    U8 *pTemp = pFrame;
    BOOL bRet = TRUE;

    tempLength = fifo_current_length(this);

    if (!fifo_output_byte(this, pLength))
    {
        bRet = FALSE;
    }
    else
    {
        if ((*pLength > tempLength) || (*pLength == ((U8)0)))
        {
            this->mFIFOHead = this->mFIFOTail;
            bRet = FALSE;
        }
        else
        {
            for (i = 0x00; i < *pLength; i++)
            {
                if (fifo_output_byte(this, &tempVal))
                {
                    *pTemp++ = tempVal;
                }
                else
                {
                    bRet = FALSE;
                    continue;
                }
            }
        }
     }

    return bRet;
}


/*---Private----------------------------------------------------------*/

/*******************************************************************************
**  FUNCTION      : fifo_is_empty
**  DESCRIPTION   : This function check whether the FIFO is empty.
**  PARAMETERS    : this:
**  RETURN        : BOOL
*******************************************************************************/
static BOOL fifo_is_empty(FIFO_TYPE *this  )
{
    if (this->mFIFOHead == this->mFIFOTail)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/*******************************************************************************
**  FUNCTION      : fifo_is_full
**  DESCRIPTION   : This function check whether the FIFO is full.
**  PARAMETERS    : this
**  RETURN        : BOOL
*******************************************************************************/
static BOOL fifo_is_full(FIFO_TYPE *this  )
{
    BOOL bRet = FALSE;
    if (this->mFIFOHead)
    {
        if (this->mFIFOTail == (this->mFIFOHead - 0x01u))
        {
            bRet = TRUE;
        }
        else
        {
            /*nothing to do*/
        }
    }
    else if (this->mFIFOTail == (this->mFIFOSize - 0x01u))
    {
        bRet = TRUE;
    }
    else
    {
        /*nothing to do*/
    }

    return bRet;
}

/*******************************************************************************
**  FUNCTION      : fifo_input_byte
**  DESCRIPTION   : This function input a byte into FIFO.
**  PARAMETERS    : this
**                  byte
**  RETURN        : BOOL
*******************************************************************************/
static BOOL fifo_input_byte( FIFO_TYPE *this , unsigned char byte )
{
    BOOL bRet = FALSE;
    
    if (!fifo_is_full(this))
    {
        if (this->mFIFOTail < this->mFIFOSize)
        {
            this->mpFIFOBuffer[this->mFIFOTail] = byte;
            this->mFIFOTail++;

            if (this->mFIFOTail >= this->mFIFOSize)
            {
                this->mFIFOTail = 0x00;
            }
            else
            {
                /*nothing to do*/
            }
            bRet = TRUE;
        }
        else
        {
            /*nothing to do*/
        }
    }
    else
    {
        /*nothing to do*/
    }
    return bRet;
}

/*******************************************************************************
**  FUNCTION      : fifo_input_byte
**  DESCRIPTION   : This function input a byte into FIFO.
**  PARAMETERS    : this
**                  byte
**  RETURN        : BOOL
*******************************************************************************/
static BOOL fifo_output_byte(FIFO_TYPE *this, U8 *pdata)
{
    BOOL bRet = FALSE;
    if (!fifo_is_empty(this))
    {
        if (this->mFIFOHead < this->mFIFOSize)
        {
            *pdata = this->mpFIFOBuffer[this->mFIFOHead];
            this->mFIFOHead++;

            if (this->mFIFOHead >= this->mFIFOSize)
            {
                this->mFIFOHead = 0x00;
            }
            else
            {
                /*nothing to do*/
            }
            bRet = TRUE;
        }
        else
        {
            /*nothing to do*/
        }
    }
    else
    {
        /*nothing to do*/
    }
    return bRet;
}


/*******************************************************************************
**  FUNCTION      : fifo_have_enough_space
**  DESCRIPTION   : This function judge fifo buffer have enough space to
                    the current length of FIFO buffer
**  PARAMETERS    : this
**  RETURN        : U16
*******************************************************************************/
 BOOL fifo_have_enough_space(FIFO_TYPE *this , U8 nBytes)
{
    /*this buffer have one byte canot be used.
      we shoult input one length byte + n data byte to FIFO buffer*/
    if ((this->mFIFOSize - fifo_current_length(this) - 0x01u) >=  ((U16)nBytes + 0x01u))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*******************************************************************************
**  FUNCTION      : fifo_current_length
**  DESCRIPTION   : This function return the current length of FIFO buffer
**  PARAMETERS    : this
**  RETURN        : U16
*******************************************************************************/
U16 fifo_current_length(FIFO_TYPE *this  )
{
    U16 retVal;

    if (this->mFIFOTail > this->mFIFOHead)
    {
        retVal = this->mFIFOTail - this->mFIFOHead;
    }
    else
    {
        if (this->mFIFOHead == this->mFIFOTail)
        {
            retVal = 0x00;
        }
        else
        {
            retVal = this->mFIFOSize - (this->mFIFOHead - this->mFIFOTail);
        }
    }
    return (retVal);
}

/*888 replaced*/
BOOL fifo_has_enough_space(FIFO_TYPE *this , U8 nBytes)
{
    if ((this->mFIFOSize - this->mFIFOLength) >= nBytes)
        return TRUE;
    else
        return FALSE;
}

/**************** END OF FILE *****************************************/

