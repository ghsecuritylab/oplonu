/*
 * Copyright (c) 2007-2009 Atheros Communications, Inc.
 * All rights reserved.
 *
 */
/**
 * @defgroup isis_port_ctrl ISIS_PORT_CONTROL
 * @{
 */
#include "sw.h"
#include "hsl.h"
#include "hsl_dev.h"
#include "hsl_port_prop.h"
#include "isis_port_ctrl.h"
#include "isis_reg.h"
#include "f1_phy.h"

static sw_error_t
_isis_port_duplex_set(a_uint32_t dev_id, fal_port_t port_id,
                      fal_port_duplex_t duplex)
{
    sw_error_t rv;
    a_uint32_t phy_id = 0;
    a_uint32_t reg_save = 0;
    a_uint32_t reg_val = 0;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    if (FAL_DUPLEX_BUTT <= duplex) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    //save reg value  
    HSL_REG_ENTRY_GET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg_val), sizeof (a_uint32_t));
    reg_save = reg_val;

    SW_SET_REG_BY_FIELD(PORT_STATUS, LINK_EN, 0, reg_val);
    SW_SET_REG_BY_FIELD(PORT_STATUS, RXMAC_EN, 0, reg_val);
    SW_SET_REG_BY_FIELD(PORT_STATUS, TXMAC_EN, 0, reg_val);

    //set mac be config by sw   and turn off RX TX MAC_EN   
    HSL_REG_ENTRY_SET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg_val), sizeof (a_uint32_t));

    rv = f1_phy_set_duplex(dev_id, phy_id, duplex);

    //retore reg value   
    HSL_REG_ENTRY_SET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg_save), sizeof (a_uint32_t));

    return rv;
}

static sw_error_t
_isis_port_duplex_get(a_uint32_t dev_id, fal_port_t port_id,
                      fal_port_duplex_t * pduplex)
{
    sw_error_t rv;
    a_uint32_t phy_id;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_get_duplex(dev_id, phy_id, pduplex);
    return rv;
}

static sw_error_t
_isis_port_speed_set(a_uint32_t dev_id, fal_port_t port_id,
                     fal_port_speed_t speed)
{
    sw_error_t rv;
    a_uint32_t phy_id = 0;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    if (FAL_SPEED_100 < speed) {
        return SW_BAD_PARAM;
    }

    rv = f1_phy_set_speed(dev_id, phy_id, speed);

    return rv;
}

static sw_error_t
_isis_port_speed_get(a_uint32_t dev_id, fal_port_t port_id,
                     fal_port_speed_t * pspeed)
{
    sw_error_t rv;
    a_uint32_t phy_id;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_get_speed(dev_id, phy_id, pspeed);

    return rv;
}

static sw_error_t
_isis_port_autoneg_status_get(a_uint32_t dev_id, fal_port_t port_id,
                              a_bool_t * status)
{
    a_uint32_t phy_id;
    sw_error_t rv;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    *status = f1_phy_autoneg_status(dev_id, phy_id);

    return SW_OK;
}

static sw_error_t
_isis_port_autoneg_enable(a_uint32_t dev_id, fal_port_t port_id)
{
    sw_error_t rv;
    a_uint32_t phy_id;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_enable_autoneg(dev_id, phy_id);
    return rv;
}

static sw_error_t
_isis_port_autoneg_disable(a_uint32_t dev_id, fal_port_t port_id)
{
    sw_error_t rv;
    a_uint32_t phy_id;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_disable_autoneg(dev_id, phy_id);
    return rv;
}


static sw_error_t
_isis_port_autoneg_restart(a_uint32_t dev_id, fal_port_t port_id)
{
    sw_error_t rv;
    a_uint32_t phy_id;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_restart_autoneg(dev_id, phy_id);
    return rv;
}

static sw_error_t
_isis_port_autoneg_adv_set(a_uint32_t dev_id, fal_port_t port_id,
                           a_uint32_t autoadv)
{
    sw_error_t rv;
    a_uint32_t phy_id;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_set_autoneg_adv(dev_id, phy_id, autoadv);
    SW_RTN_ON_ERROR(rv);

    return SW_OK;
}

static sw_error_t
_isis_port_autoneg_adv_get(a_uint32_t dev_id, fal_port_t port_id,
                           a_uint32_t * autoadv)
{
    sw_error_t rv;
    a_uint32_t phy_id;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    *autoadv = 0;
    rv = f1_phy_get_autoneg_adv(dev_id, phy_id, autoadv);
    SW_RTN_ON_ERROR(rv);

    return SW_OK;
}

static sw_error_t
_isis_port_flowctrl_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable)
{
    sw_error_t rv;
    a_uint32_t val, force, reg;

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    if (A_TRUE == enable) {
        val = 1;
    } else if (A_FALSE == enable) {
        val = 0;
    } else {
        return SW_BAD_PARAM;
    }

    HSL_REG_ENTRY_GET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    SW_GET_FIELD_BY_REG(PORT_STATUS, FLOW_LINK_EN, force, reg);
    if (force) {
        /* flow control isn't in force mode so can't set */
        return SW_BAD_STATE;
    }

    SW_SET_REG_BY_FIELD(PORT_STATUS, RX_FLOW_EN, val, reg);
    SW_SET_REG_BY_FIELD(PORT_STATUS, TX_FLOW_EN, val, reg);
    SW_SET_REG_BY_FIELD(PORT_STATUS, TX_HALF_FLOW_EN, val, reg);

    HSL_REG_ENTRY_SET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    return rv;
}

static sw_error_t
_isis_port_flowctrl_get(a_uint32_t dev_id, fal_port_t port_id,
                        a_bool_t * enable)
{
    sw_error_t rv;
    a_uint32_t tx, rx, reg;

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    HSL_REG_ENTRY_GET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    SW_GET_FIELD_BY_REG(PORT_STATUS, RX_FLOW_EN, rx, reg);
    SW_GET_FIELD_BY_REG(PORT_STATUS, TX_FLOW_EN, tx, reg);

    if (1 == rx) {
        *enable = A_TRUE;
    } else {
        *enable = A_FALSE;
    }

    return SW_OK;
}

static inline sw_error_t
_opl_port_flowctrl_set(a_uint32_t dev_id, fal_port_t port_id,
                                   a_bool_t enable)
{
    sw_error_t rv;
    a_uint32_t force, reg;

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    HSL_REG_ENTRY_GET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    if (A_TRUE == enable) {
        SW_SET_REG_BY_FIELD(PORT_STATUS, FLOW_LINK_EN, 0, reg);
        SW_SET_REG_BY_FIELD(PORT_STATUS, TX_FLOW_EN, 1, reg);
        SW_SET_REG_BY_FIELD(PORT_STATUS, RX_FLOW_EN, 1, reg);
        SW_SET_REG_BY_FIELD(PORT_STATUS, TX_HALF_FLOW_EN, 1, reg);
    }
	else if (A_FALSE == enable) {
        SW_SET_REG_BY_FIELD(PORT_STATUS, FLOW_LINK_EN, 0, reg);
        SW_SET_REG_BY_FIELD(PORT_STATUS, TX_FLOW_EN, 0, reg);
        SW_SET_REG_BY_FIELD(PORT_STATUS, RX_FLOW_EN, 0, reg);
        SW_SET_REG_BY_FIELD(PORT_STATUS, TX_HALF_FLOW_EN, 0, reg);
    }
	else {
        return SW_BAD_PARAM;
    }

    HSL_REG_ENTRY_SET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    return rv;
}

static sw_error_t
_isis_port_flowctrl_forcemode_set(a_uint32_t dev_id, fal_port_t port_id,
                                  a_bool_t enable)
{
    sw_error_t rv;
    a_uint32_t force, reg;

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    HSL_REG_ENTRY_GET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    SW_GET_FIELD_BY_REG(PORT_STATUS, FLOW_LINK_EN, force, reg);
    if (force != (a_uint32_t) enable) {
        return SW_OK;
    }

    if (A_TRUE == enable) {
        SW_SET_REG_BY_FIELD(PORT_STATUS, FLOW_LINK_EN, 0, reg);
        SW_SET_REG_BY_FIELD(PORT_STATUS, TX_FLOW_EN, 0, reg);
        SW_SET_REG_BY_FIELD(PORT_STATUS, RX_FLOW_EN, 0, reg);
    } else if (A_FALSE == enable) {
        SW_SET_REG_BY_FIELD(PORT_STATUS, FLOW_LINK_EN, 1, reg);
    } else {
        return SW_BAD_PARAM;
    }
    SW_SET_REG_BY_FIELD(PORT_STATUS, TX_HALF_FLOW_EN, 0, reg);

    HSL_REG_ENTRY_SET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    return rv;
}

static sw_error_t
_isis_port_flowctrl_forcemode_get(a_uint32_t dev_id, fal_port_t port_id,
                                  a_bool_t * enable)
{
    sw_error_t rv;
    a_uint32_t force, reg;

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    HSL_REG_ENTRY_GET(rv, dev_id, PORT_STATUS, port_id,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    SW_GET_FIELD_BY_REG(PORT_STATUS, FLOW_LINK_EN, force, reg);
    if (0 == force) {
        *enable = A_TRUE;
    } else {
        *enable = A_FALSE;
    }

    return SW_OK;
}

static sw_error_t
_isis_port_powersave_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable)
{
    sw_error_t rv;
    a_uint32_t phy_id = 0;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_set_powersave(dev_id, phy_id, enable);

    return rv;
}

static sw_error_t
_isis_port_powersave_get(a_uint32_t dev_id, fal_port_t port_id,
                         a_bool_t * enable)
{
    sw_error_t rv;
    a_uint32_t phy_id = 0;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_get_powersave(dev_id, phy_id, enable);

    return rv;
}

static sw_error_t
_isis_port_hibernate_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable)
{
    sw_error_t rv;
    a_uint32_t phy_id = 0;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_set_hibernate(dev_id, phy_id, enable);

    return rv;
}

static sw_error_t
_isis_port_hibernate_get(a_uint32_t dev_id, fal_port_t port_id,
                         a_bool_t * enable)
{
    sw_error_t rv;
    a_uint32_t phy_id = 0;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_get_hibernate(dev_id, phy_id, enable);

    return rv;
}

static sw_error_t
_isis_port_cdt(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t mdi_pair,
               fal_cable_status_t * cable_status, a_uint32_t * cable_len)
{
    sw_error_t rv;
    a_uint32_t phy_id = 0;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    rv = f1_phy_cdt(dev_id, phy_id, mdi_pair, cable_status, cable_len);

    return rv;
}

static sw_error_t
_isis_port_rxhdr_mode_set(a_uint32_t dev_id, fal_port_t port_id,
                          fal_port_header_mode_t mode)
{
    sw_error_t rv;
    a_uint32_t val;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    if (FAL_NO_HEADER_EN == mode) {
        val = 0;
    } else if (FAL_ONLY_MANAGE_FRAME_EN == mode) {
        val = 1;
    } else if (FAL_ALL_TYPE_FRAME_EN == mode) {
        val = 2;
    } else {
        return SW_BAD_PARAM;
    }

    HSL_REG_FIELD_SET(rv, dev_id, PORT_HDR_CTL, port_id, RXHDR_MODE,
                      (a_uint8_t *) (&val), sizeof (a_uint32_t));
    return rv;
}

static sw_error_t
_isis_port_rxhdr_mode_get(a_uint32_t dev_id, fal_port_t port_id,
                          fal_port_header_mode_t * mode)
{
    sw_error_t rv;
    a_uint32_t val;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    HSL_REG_FIELD_GET(rv, dev_id, PORT_HDR_CTL, port_id, RXHDR_MODE,
                      (a_uint8_t *) (&val), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    if (1 == val) {
        *mode = FAL_ONLY_MANAGE_FRAME_EN;
    } else if (2 == val) {
        *mode = FAL_ALL_TYPE_FRAME_EN;
    } else {
        *mode = FAL_NO_HEADER_EN;
    }

    return SW_OK;
}

static sw_error_t
_isis_port_txhdr_mode_set(a_uint32_t dev_id, fal_port_t port_id,
                          fal_port_header_mode_t mode)
{
    sw_error_t rv;
    a_uint32_t val;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    if (FAL_NO_HEADER_EN == mode) {
        val = 0;
    } else if (FAL_ONLY_MANAGE_FRAME_EN == mode) {
        val = 1;
    } else if (FAL_ALL_TYPE_FRAME_EN == mode) {
        val = 2;
    } else {
        return SW_BAD_PARAM;
    }

    HSL_REG_FIELD_SET(rv, dev_id, PORT_HDR_CTL, port_id, TXHDR_MODE,
                      (a_uint8_t *) (&val), sizeof (a_uint32_t));
    return rv;
}

static sw_error_t
_isis_port_txhdr_mode_get(a_uint32_t dev_id, fal_port_t port_id,
                          fal_port_header_mode_t * mode)
{
    sw_error_t rv;
    a_uint32_t val;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        return SW_BAD_PARAM;
    }

    HSL_REG_FIELD_GET(rv, dev_id, PORT_HDR_CTL, port_id, TXHDR_MODE,
                      (a_uint8_t *) (&val), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    if (1 == val) {
        *mode = FAL_ONLY_MANAGE_FRAME_EN;
    } else if (2 == val) {
        *mode = FAL_ALL_TYPE_FRAME_EN;
    } else {
        *mode = FAL_NO_HEADER_EN;
    }

    return SW_OK;
}

static sw_error_t
_isis_header_type_set(a_uint32_t dev_id, a_bool_t enable, a_uint32_t type)
{
    a_uint32_t reg;
    sw_error_t rv;

    HSL_DEV_ID_CHECK(dev_id);

    HSL_REG_ENTRY_GET(rv, dev_id, HEADER_CTL, 0,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    if (A_TRUE == enable) {
        if (0xffff < type) {
            return SW_BAD_PARAM;
        }
        SW_SET_REG_BY_FIELD(HEADER_CTL, TYPE_LEN, 1, reg);
        SW_SET_REG_BY_FIELD(HEADER_CTL, TYPE_VAL, type, reg);
    } else if (A_FALSE == enable) {
        SW_SET_REG_BY_FIELD(HEADER_CTL, TYPE_LEN, 0, reg);
        SW_SET_REG_BY_FIELD(HEADER_CTL, TYPE_VAL, 0, reg);
    } else {
        return SW_BAD_PARAM;
    }

    HSL_REG_ENTRY_SET(rv, dev_id, HEADER_CTL, 0,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    return rv;
}

static sw_error_t
_isis_header_type_get(a_uint32_t dev_id, a_bool_t * enable, a_uint32_t * type)
{
    a_uint32_t data, reg;
    sw_error_t rv;

    HSL_DEV_ID_CHECK(dev_id);

    HSL_REG_ENTRY_GET(rv, dev_id, HEADER_CTL, 0,
                      (a_uint8_t *) (&reg), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    SW_GET_FIELD_BY_REG(HEADER_CTL, TYPE_LEN, data, reg);
    if (data) {
        SW_GET_FIELD_BY_REG(HEADER_CTL, TYPE_VAL, data, reg);
        *enable = A_TRUE;
        *type = data;
    } else {
        *enable = A_FALSE;
        *type = 0;
    }

    return SW_OK;
}

/**
 * @brief Set duplex mode on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[in] duplex duplex mode
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_duplex_set(a_uint32_t dev_id, fal_port_t port_id,
                     fal_port_duplex_t duplex)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_duplex_set(dev_id, port_id, duplex);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get duplex mode on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] duplex duplex mode
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_duplex_get(a_uint32_t dev_id, fal_port_t port_id,
                     fal_port_duplex_t * pduplex)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_duplex_get(dev_id, port_id, pduplex);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Set speed on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[in] speed port speed
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_speed_set(a_uint32_t dev_id, fal_port_t port_id,
                    fal_port_speed_t speed)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_speed_set(dev_id, port_id, speed);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get speed on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] speed port speed
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_speed_get(a_uint32_t dev_id, fal_port_t port_id,
                    fal_port_speed_t * pspeed)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_speed_get(dev_id, port_id, pspeed);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get auto negotiation status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] status A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_autoneg_status_get(a_uint32_t dev_id, fal_port_t port_id,
                             a_bool_t * status)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_autoneg_status_get(dev_id, port_id, status);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Enable auto negotiation status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_autoneg_enable(a_uint32_t dev_id, fal_port_t port_id)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_autoneg_enable(dev_id, port_id);
    HSL_API_UNLOCK;
    return rv;
}

HSL_LOCAL sw_error_t
isis_port_autoneg_disable(a_uint32_t dev_id, fal_port_t port_id)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_autoneg_disable(dev_id, port_id);
    HSL_API_UNLOCK;
    return rv;
}


/**
 * @brief Restart auto negotiation procedule on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_autoneg_restart(a_uint32_t dev_id, fal_port_t port_id)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_autoneg_restart(dev_id, port_id);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Set auto negotiation advtisement ability on a particular port.
 *   @details  Comments:
 *   auto negotiation advtisement ability is defined by macro such as
 *   FAL_PHY_ADV_10T_HD, FAL_PHY_ADV_PAUSE...
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[in] autoadv auto negotiation advtisement ability bit map
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_autoneg_adv_set(a_uint32_t dev_id, fal_port_t port_id,
                          a_uint32_t autoadv)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_autoneg_adv_set(dev_id, port_id, autoadv);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get auto negotiation advtisement ability on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] autoadv auto negotiation advtisement ability bit map
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_autoneg_adv_get(a_uint32_t dev_id, fal_port_t port_id,
                          a_uint32_t * autoadv)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_autoneg_adv_get(dev_id, port_id, autoadv);
    HSL_API_UNLOCK;
    return rv;
}

HSL_LOCAL sw_error_t
isis_port_autoneg_done_read(a_uint32_t dev_id, fal_port_t port_id, 
                                              a_bool_t * status)
{
    sw_error_t rv;
    a_uint32_t phy_id;

	HSL_API_LOCK;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    *status = f1_autoneg_done(dev_id, phy_id);
	
  	HSL_API_UNLOCK;
  
    return SW_OK;
}

/**
 * @brief Set flow control status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[in] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_flowctrl_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_flowctrl_set(dev_id, port_id, enable);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get flow control status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_flowctrl_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_flowctrl_get(dev_id, port_id, enable);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Set flow control force mode on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
opl_port_flowctrl_set(a_uint32_t dev_id, fal_port_t port_id,
                                   a_bool_t enable)
{
    sw_error_t rv;
	a_uint32_t autoadv;

    HSL_API_LOCK;
    rv = _opl_port_flowctrl_set(dev_id, port_id, enable);	
    HSL_API_UNLOCK;
	
	rv = isis_port_autoneg_adv_get(dev_id,port_id, &autoadv);

	if (enable)
	{
		autoadv |= FAL_PHY_ADV_PAUSE;
		autoadv |= FAL_PHY_ADV_ASY_PAUSE;
	}
	else
	{
		autoadv &= ~FAL_PHY_ADV_PAUSE;
		autoadv &= ~FAL_PHY_ADV_ASY_PAUSE;
	}		

	rv = isis_port_autoneg_adv_set(dev_id,port_id, autoadv);		
	
    return rv;
}

/**
 * @brief Set flow control force mode on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_flowctrl_forcemode_set(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t enable)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_flowctrl_forcemode_set(dev_id, port_id, enable);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get flow control force mode on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_flowctrl_forcemode_get(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t * enable)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_flowctrl_forcemode_get(dev_id, port_id, enable);
    HSL_API_UNLOCK;
    return rv;
}

HSL_LOCAL sw_error_t
isis_port_eg_mac_base_vlan_set(a_uint32_t dev_id, fal_port_t port_id,
                           a_bool_t enable)
{
    sw_error_t rv;
    a_uint32_t val;

    HSL_API_LOCK;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
		HSL_API_UNLOCK;
        return SW_BAD_PARAM;
    }

    if (A_TRUE == enable) {
        val = 1;
    } else if (A_FALSE == enable) {
        val = 0;
    } else {
    	HSL_API_UNLOCK;
        return SW_BAD_PARAM;
    }

    HSL_REG_FIELD_SET(rv, dev_id, PRI_CTL, port_id, EG_MAC_BASE_VLAN_EN,
                      (a_uint8_t *) (&val), sizeof (a_uint32_t));


	HSL_API_UNLOCK;

    return rv;
}


/**
 * @brief Set MAC loop back  on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[in] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_lpbk_set(a_uint32_t dev_id, fal_port_t port_id,
                           a_bool_t enable)
{
    sw_error_t rv;
    a_uint32_t val;
    a_uint32_t phy_id = 0;

    HSL_API_LOCK;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
	HSL_API_UNLOCK;
        return SW_BAD_PARAM;
    }

    if (A_TRUE == enable) {
        val = 1;
    } else if (A_FALSE == enable) {
        val = 0;
    } else {
    	HSL_API_UNLOCK;
        return SW_BAD_PARAM;
    }

    HSL_REG_FIELD_SET(rv, dev_id, PORT_LOOKUP_CTL, port_id, PORT_LOOP_BACK,
                      (a_uint8_t *) (&val), sizeof (a_uint32_t));

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);

	f1_phy_set_lpbk(dev_id, phy_id, enable);

	HSL_API_UNLOCK;

    return rv;
}


/**
 * @brief Get MAC loop back  on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_lpbk_get(a_uint32_t dev_id, fal_port_t port_id,
                           a_bool_t * enable)
{
    sw_error_t rv;
    a_uint32_t val;

    HSL_API_LOCK;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
		HSL_API_UNLOCK;
		return SW_BAD_PARAM;
    }

    HSL_REG_FIELD_GET(rv, dev_id, PORT_LOOKUP_CTL, port_id, PORT_LOOP_BACK,
                      (a_uint8_t *) (&val), sizeof (a_uint32_t));
    SW_RTN_ON_ERROR(rv);

    if (1 == val) {
        *enable = A_TRUE;
    } else {
        *enable = A_FALSE;
    }

	HSL_API_UNLOCK;

    return rv;
}


/**
 * @brief Get link status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_link_status_get(a_uint32_t dev_id, fal_port_t port_id,
        a_bool_t *up)
{
    sw_error_t rv;
    a_uint32_t phy_id;

	HSL_API_LOCK;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    *up = f1_phy_get_link_status(dev_id, phy_id);

	HSL_API_UNLOCK;

    return rv;
}



/**
 * @brief Get admin status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_admin_status_get(a_uint32_t dev_id, fal_port_t port_id,
        a_bool_t *up)
{
    sw_error_t rv;
    a_uint32_t phy_id;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_PHY)) {
        return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
    SW_RTN_ON_ERROR(rv);

    *up = f1_phy_get_power(dev_id, phy_id);

    return rv;
}



/**
 * @brief Set powersaving status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_powersave_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_powersave_set(dev_id, port_id, enable);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get powersaving status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_powersave_get(a_uint32_t dev_id, fal_port_t port_id,
                        a_bool_t * enable)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_powersave_get(dev_id, port_id, enable);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Set hibernate status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_hibernate_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_hibernate_set(dev_id, port_id, enable);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get hibernate status on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_hibernate_get(a_uint32_t dev_id, fal_port_t port_id,
                        a_bool_t * enable)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_hibernate_get(dev_id, port_id, enable);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Run cable diagnostic test on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[in] mdi_pair mdi pair id
 * @param[out] cable_status cable status
 * @param[out] cable_len cable len
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_cdt(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t mdi_pair,
              fal_cable_status_t * cable_status, a_uint32_t * cable_len)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_cdt(dev_id, port_id, mdi_pair, cable_status, cable_len);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Set status of Atheros header packets parsed on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[in] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_rxhdr_mode_set(a_uint32_t dev_id, fal_port_t port_id,
                         fal_port_header_mode_t mode)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_rxhdr_mode_set(dev_id, port_id, mode);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get status of Atheros header packets parsed on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_rxhdr_mode_get(a_uint32_t dev_id, fal_port_t port_id,
                         fal_port_header_mode_t * mode)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_rxhdr_mode_get(dev_id, port_id, mode);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Set status of Atheros header packets parsed on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[in] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_txhdr_mode_set(a_uint32_t dev_id, fal_port_t port_id,
                         fal_port_header_mode_t mode)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_txhdr_mode_set(dev_id, port_id, mode);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get status of Atheros header packets parsed on a particular port.
 * @param[in] dev_id device id
 * @param[in] port_id port id
 * @param[out] enable A_TRUE or A_FALSE
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_port_txhdr_mode_get(a_uint32_t dev_id, fal_port_t port_id,
                         fal_port_header_mode_t * mode)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_port_txhdr_mode_get(dev_id, port_id, mode);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Set status of Atheros header type value on a particular device.
 * @param[in] dev_id device id
 * @param[in] enable A_TRUE or A_FALSE
 * @param[in] type header type value
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_header_type_set(a_uint32_t dev_id, a_bool_t enable, a_uint32_t type)
{
    sw_error_t rv;
    HSL_API_LOCK;
    rv = _isis_header_type_set(dev_id, enable, type);
    HSL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get status of Atheros header type value on a particular device.
 * @param[in] dev_id device id
 * @param[out] enable A_TRUE or A_FALSE
 * @param[out] type header type value
 * @return SW_OK or error code
 */
HSL_LOCAL sw_error_t
isis_header_type_get(a_uint32_t dev_id, a_bool_t * enable, a_uint32_t * type)
{
    sw_error_t rv;

    HSL_API_LOCK;
    rv = _isis_header_type_get(dev_id, enable, type);
    HSL_API_UNLOCK;
    return rv;
}

sw_error_t
isis_port_ctrl_init(a_uint32_t dev_id)
{
    HSL_DEV_ID_CHECK(dev_id);

#ifndef HSL_STANDALONG
    {
        hsl_api_t *p_api;

        SW_RTN_ON_NULL(p_api = hsl_api_ptr_get(dev_id));

        p_api->port_duplex_get = isis_port_duplex_get;
        p_api->port_duplex_set = isis_port_duplex_set;
        p_api->port_speed_get = isis_port_speed_get;
        p_api->port_speed_set = isis_port_speed_set;
        p_api->port_autoneg_status_get = isis_port_autoneg_status_get;
        p_api->port_autoneg_enable = isis_port_autoneg_enable;
        p_api->port_autoneg_restart = isis_port_autoneg_restart;
        p_api->port_autoneg_adv_get = isis_port_autoneg_adv_get;
        p_api->port_autoneg_adv_set = isis_port_autoneg_adv_set;
        p_api->port_flowctrl_set = isis_port_flowctrl_set;
        p_api->port_flowctrl_get = isis_port_flowctrl_get;
        p_api->port_flowctrl_forcemode_set = isis_port_flowctrl_forcemode_set;
        p_api->port_flowctrl_forcemode_get = isis_port_flowctrl_forcemode_get;
        p_api->port_powersave_set = isis_port_powersave_set;
        p_api->port_powersave_get = isis_port_powersave_get;
        p_api->port_hibernate_set = isis_port_hibernate_set;
        p_api->port_hibernate_get = isis_port_hibernate_get;
        p_api->port_cdt = isis_port_cdt;
        p_api->port_rxhdr_mode_set = isis_port_rxhdr_mode_set;
        p_api->port_rxhdr_mode_get = isis_port_rxhdr_mode_get;
        p_api->port_txhdr_mode_set = isis_port_txhdr_mode_set;
        p_api->port_txhdr_mode_get = isis_port_txhdr_mode_get;
        p_api->header_type_set = isis_header_type_set;
        p_api->header_type_get = isis_header_type_get;
    }
#endif

    return SW_OK;
}


HSL_LOCAL sw_error_t
isis_port_shutdown_set_only(a_uint32_t dev_id, fal_port_t port_id,
                           a_bool_t enable)
{
    sw_error_t rv;
    a_uint32_t val;
    a_uint32_t phy_id = 0;

    HSL_API_LOCK;

    HSL_DEV_ID_CHECK(dev_id);

    if (A_TRUE != hsl_port_prop_check(dev_id, port_id, HSL_PP_INCL_CPU)) {
        HSL_API_UNLOCK;
		return SW_BAD_PARAM;
    }

    rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);

	if (enable)
	{
		f1_phy_poweroff(dev_id, phy_id);
	}
	else
	{
		f1_phy_poweron( dev_id, phy_id);
	}

	HSL_API_UNLOCK;

    return rv;

}

sw_error_t isis_set_port_enable(a_uint32_t dev_id, fal_port_t portid, char mode)
{
	a_uint16_t phy_data = 0;
	sw_error_t status = SW_FAIL;

	HSL_API_LOCK;

       HSL_DEV_ID_CHECK(dev_id);

       if (A_TRUE != hsl_port_prop_check(dev_id, portid, HSL_PP_INCL_CPU)) {
           HSL_API_UNLOCK;
		return SW_BAD_PARAM;
       }


	status = isis_phy_get(dev_id, portid,0, &phy_data);
	
	if(status != SW_OK)
	  {
		printf("\nisis_phy_get error, error num %d, file %s, line %d\n",status,__FILE__,__LINE__);
		return status;
	  }
	
	if(mode)
	{
		phy_data &= 0xf7ff;
		status = isis_phy_set(dev_id, portid,0, phy_data);
	}
	else
	{
		phy_data |= 0x800;
		status = isis_phy_set(dev_id, portid,0, phy_data);
	}
	
	if(status != SW_OK)
	  {
		printf("\nisis_phy_set error, error num %d, file %s, line %d\n",status,__FILE__,__LINE__);
		return status;
	  }
	
        return SW_OK;
}

sw_error_t isis_get_port_enable(a_uint32_t dev_id, fal_port_t portid, char *pMode)
{
	a_uint16_t phy_data = 0;
	sw_error_t status = SW_FAIL;

	HSL_API_LOCK;

       HSL_DEV_ID_CHECK(dev_id);

       if (A_TRUE != hsl_port_prop_check(dev_id, portid, HSL_PP_INCL_CPU)) {
           HSL_API_UNLOCK;
		return SW_BAD_PARAM;
       }

	if(pMode == NULL)
	  {
		printf("\ninput point is NULL, file %s, line %d\n",__FILE__,__LINE__);
		return SW_BAD_PTR;
	  }
	

	status = isis_phy_get(dev_id, portid,0, &phy_data);
	
	if(status != SW_OK)
	  {
		printf("\nisis_phy_get error, error num %d, file %s, line %d\n",status,__FILE__,__LINE__);
		return status;
	  }
	
	phy_data &= 0x0800;

	if(phy_data)
	  {
		*pMode = 0;
	  }
	else
	  {
		*pMode = 1;
	  }
	
return SW_OK;
}

/**
 * @}
 */

