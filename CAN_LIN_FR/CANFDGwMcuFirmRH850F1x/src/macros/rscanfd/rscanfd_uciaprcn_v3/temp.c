/*
 * temp.c
 *
 *  Created on: 2018Äê9ÔÂ17ÈÕ
 *      Author: a5059726
 */

const struct ee_rscfd_cfg_global EE_RSCFD_A_GCFG_SWGW = {

  {
    EE_RSCFD_TXPRIO_ID,                      /* TX priority by ID (standard) */
    EE_RSCFD_DLCCHECK_DISABLE,
    EE_RSCFD_DLCREPL_DISABLE,                 /* no DLC check or replacement */
    EE_RSCFD_MIRROR_DISABLE,                               /* no Mirror Mode */
    EE_RSCFD_CLOCK_SYS,                              /* use peripheral clock */
    EE_RSCFD_PLOVF_TRUNCATE, 0, /* larger messages than buffer are truncated */
    0, EE_RSCFD_CLOCK_TSBIT,
    EE_RSCFD_CHANNEL0,          /* Use 1TQ Bit-Timing clock 0 for Timestamps */
    EE_RSCFD_CLOCK_FIFO_OFF               /* interval timer of FIFO disabled */
  },
  {
    EE_RSCFD_OPMODE_KEEP,
    EE_RSCFD_SLEEP_DISABLE, 0,       /* No implicit change of Operation Mode */
    EE_RSCFD_GINT_NONE, 0,                            /* No Error Interrupts */
    EE_RSCFD_TIMESTAMP_RESET,                             /* Timestamp reset */
    EE_RSCFD_TIMESTAMP_KEEP, 0       /* Timestamp is not written by software */
  },
  {
  	EE_RSCFD_PROTEXCEVENT_EN, 0, /* enable protocol exception event handling */
  	EE_RSCFD_TSCAPTURE_SOF, 0      /* timestamp capture performed at SOF bit */
  },
  {
  	EE_RSCFD_PROTOCOL_ISO, 0        /* use ISO conformous CRC field protocol */
  },
  {
  	1,                                        /* use one classical RX buffer */
  	EE_RSCFD_BUFDL_64, 0         /* full 64-byte size of classical RX buffer */
  },
  {
	  2, 2, 2, 2, 2, 2, 2, 2  	          /* every channel has two AFL entries */
  },
  {
    EE_RSCFD_A_RXFIFO_SWGW,                           /* enable all RX FIFOs */
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW
  }
};
