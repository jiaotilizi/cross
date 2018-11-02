/*
 * $Id: dport.c,v 1.7 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *
 *
 */

#include <shared/bsl.h>

#include <sal/core/libc.h>

#include <soc/drv.h>
#include <soc/debug.h>
#include <soc/error.h>
#include <soc/dport.h>

int
soc_dport_to_port(int unit, soc_port_t dport)
{
    if ((SOC_DPORT_MAP_FLAGS(unit) & SOC_DPORT_MAP_F_ENABLE) == 0) {
        if (SOC_PORT_VALID(unit, dport)) {
            return dport;
        }
        return -1;
    }

    if (dport >= 0 && dport < COUNTOF(SOC_DPORT_MAP(unit))) {
        return SOC_DPORT_MAP(unit)[dport];
    }

    return -1;
}

int
soc_dport_from_port(int unit, soc_port_t port)
{
    if ((SOC_DPORT_MAP_FLAGS(unit) & SOC_DPORT_MAP_F_ENABLE) == 0) {
        if (SOC_PORT_VALID(unit, port)) {
            return port;
        }
        return -1;
    }

    if (port >= 0 && port < COUNTOF(SOC_DPORT_RMAP(unit))) {
        return SOC_DPORT_RMAP(unit)[port];
    }

    return -1;
}

int
soc_dport_from_dport_idx(int unit, soc_port_t dport, int idx)
{
    if ((SOC_DPORT_MAP_FLAGS(unit) & SOC_DPORT_MAP_F_ENABLE) == 0 ||
        (SOC_DPORT_MAP_FLAGS(unit) & SOC_DPORT_MAP_F_INDEXED)) {
        return idx;
    }
    return dport;
}

int
soc_dport_map_port(int unit, soc_port_t dport, soc_port_t port)
{
    int idx;

    /* Check for valid ports */
    if (dport < 0 || dport >= SOC_DPORT_MAX ||
        port < 0 || port >= SOC_PBMP_PORT_MAX) {
        LOG_WARN(BSL_LS_SOC_COMMON,
                 (BSL_META_U(unit,
                             "soc_dport_map_port: Invalid port mapping %d -> %d\n"),
                  dport, port));
        return -1;
    }

    /* Silently discard invalid ports */
    if (!SOC_PORT_VALID(unit, port)) {
        return 0;
    }

    /* Remove previous mapping if any */
    for (idx = 0; idx < COUNTOF(SOC_DPORT_MAP(unit)); idx++) {
        if (SOC_DPORT_MAP(unit)[idx] == port) {
            SOC_DPORT_MAP(unit)[idx] = -1;
        }
    }

    /* Update port map */
    SOC_DPORT_MAP(unit)[dport] = port;

    return 0;
}

int
soc_dport_map_update(int unit)
{
    int idx, port, dport;
    soc_info_t *si = &SOC_INFO(unit);

    for (idx = 0; idx < COUNTOF(SOC_DPORT_RMAP(unit)); idx++) {
        SOC_DPORT_RMAP(unit)[idx] = -1;
    }

    for (idx = 0; idx < COUNTOF(SOC_DPORT_MAP(unit)); idx++) {
        port = SOC_DPORT_MAP(unit)[idx];
        if (port >= 0) {
            SOC_DPORT_RMAP(unit)[port] = idx;
        }
    }

    idx = 0;
    /* coverity[overrun-local : FALSE] */
    SOC_DPORT_PBMP_ITER(unit, PBMP_FE_ALL(unit), dport, port) {
        sal_snprintf(si->port_name[port], sizeof(si->port_name[port]),
                     "fe%d", soc_dport_from_dport_idx(unit, dport, idx++));
    }
    idx = 0;
    /* coverity[overrun-local : FALSE] */
    SOC_DPORT_PBMP_ITER(unit, PBMP_XE_ALL(unit), dport, port) {
        sal_snprintf(si->port_name[port], sizeof(si->port_name[port]),
                     "xe%d", soc_dport_from_dport_idx(unit, dport, idx++));
    }
    idx = 0;
    /* coverity[overrun-local : FALSE] */
    SOC_DPORT_PBMP_ITER(unit, PBMP_CE_ALL(unit), dport, port) {
        sal_snprintf(si->port_name[port], sizeof(si->port_name[port]),
                     "ce%d", soc_dport_from_dport_idx(unit, dport, idx++));
    }
    idx = 0;
    /* coverity[overrun-local : FALSE] */
    SOC_DPORT_PBMP_ITER(unit, PBMP_HG_ALL(unit), dport, port) {
        sal_snprintf(si->port_name[port], sizeof(si->port_name[port]),
                     "hg%d", soc_dport_from_dport_idx(unit, dport, idx++));
    }
    idx = 0;
    /* coverity[overrun-local : FALSE] */
    SOC_DPORT_PBMP_ITER(unit, PBMP_GE_ALL(unit), dport, port) {
        sal_snprintf(si->port_name[port], sizeof(si->port_name[port]),
                     "ge%d", soc_dport_from_dport_idx(unit, dport, idx++));
    }
    idx = 0;
    /* coverity[overrun-local : FALSE] */
    SOC_DPORT_PBMP_ITER(unit, PBMP_AXP_ALL(unit), dport, port) {
        sal_snprintf(si->port_name[port], sizeof(si->port_name[port]),
                     "axp%d", soc_dport_from_dport_idx(unit, dport, idx++));
    }
    idx = 0;
    /* coverity[overrun-local : FALSE] */
    SOC_DPORT_PBMP_ITER(unit, PBMP_INTP_ALL(unit), dport, port) {
        sal_snprintf(si->port_name[port], sizeof(si->port_name[port]),
                     "intp%d", soc_dport_from_dport_idx(unit, dport, idx++));
    }

    return 0;
}
