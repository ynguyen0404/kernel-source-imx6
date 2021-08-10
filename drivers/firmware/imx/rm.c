// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017~2019 NXP
 *
 * File containing client-side RPC functions for the RM service. These
 * function are ported to clients that communicate to the SC.
 */

#include <linux/firmware/imx/svc/rm.h>

struct imx_sc_msg_rm_rsrc_owned {
	struct imx_sc_rpc_msg hdr;
	u16 resource;
} __packed __aligned(4);

/*
 * This function check @resource is owned by current partition or not
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    resource the control is associated with
 *
 * @return Returns 0 for success and < 0 for errors.
 */
bool imx_sc_rm_is_resource_owned(struct imx_sc_ipc *ipc, u16 resource)
{
	struct imx_sc_msg_rm_rsrc_owned msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_RM;
	hdr->func = IMX_SC_RM_FUNC_IS_RESOURCE_OWNED;
	hdr->size = 2;

	msg.resource = resource;

	imx_scu_call_rpc(ipc, &msg, true);

	return hdr->func;
}
EXPORT_SYMBOL(imx_sc_rm_is_resource_owned);
