/*
 * Copyright (c) 2007-2008 Atheros Communications, Inc.
 * All rights reserved.
 *
 */
#include "sw_ioctl.h"
#include "fal_acl.h"
#include "fal_uk_if.h"

sw_error_t
fal_acl_list_creat(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t prio)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_LIST_CREAT, dev_id, list_id, prio);
    return rv;
}

sw_error_t
fal_acl_list_destroy(a_uint32_t dev_id, a_uint32_t list_id)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_LIST_DESTROY, dev_id, list_id);
    return rv;
}

sw_error_t
fal_acl_rule_add(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id,
                    a_uint32_t rule_nr, fal_acl_rule_t * rule)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_RULE_ADD, dev_id, list_id, rule_id,
                                            rule_nr, (a_uint32_t) rule);
    return rv;
}

sw_error_t
fal_acl_rule_delete(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id,
                    a_uint32_t rule_nr)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_RULE_DELETE, dev_id, list_id, rule_id, rule_nr);
    return rv;
}

sw_error_t
fal_acl_rule_query(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id,
                    fal_acl_rule_t * rule)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_RULE_QUERY, dev_id, list_id, rule_id, (a_uint32_t) rule);
    return rv;
}

sw_error_t
fal_acl_list_bind(a_uint32_t dev_id, a_uint32_t list_id,
                     fal_acl_direc_t direc, fal_acl_bind_obj_t obj_t,
                     a_uint32_t obj_idx)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_LIST_BIND, dev_id, list_id, direc, obj_t, obj_idx);
    return rv;
}

sw_error_t
fal_acl_list_unbind(a_uint32_t dev_id, a_uint32_t list_id,
                       fal_acl_direc_t direc, fal_acl_bind_obj_t obj_t,
                       a_uint32_t obj_idx)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_LIST_UNBIND, dev_id, list_id, direc, obj_t, obj_idx);
    return rv;
}

sw_error_t
fal_acl_status_set(a_uint32_t dev_id, a_bool_t enable)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_STATUS_SET, dev_id, (a_uint32_t) enable);
    return rv;
}

sw_error_t
fal_acl_status_get(a_uint32_t dev_id, a_bool_t * enable)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_STATUS_GET, dev_id, (a_uint32_t) enable);
    return rv;
}

sw_error_t
fal_acl_list_dump(a_uint32_t dev_id)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_LIST_DUMP, dev_id);
    return rv;
}

sw_error_t
fal_acl_rule_dump(a_uint32_t dev_id)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_RULE_DUMP, dev_id);
    return rv;
}

sw_error_t
fal_acl_port_udf_profile_set(a_uint32_t dev_id, fal_port_t port_id, fal_acl_udf_type_t udf_type, a_uint32_t offset, a_uint32_t length)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_PT_UDF_PROFILE_SET, dev_id, port_id, udf_type, offset, length);
    return rv;
}

sw_error_t
fal_acl_port_udf_profile_get(a_uint32_t dev_id, fal_port_t port_id, fal_acl_udf_type_t udf_type, a_uint32_t * offset, a_uint32_t * length)
{
    sw_error_t rv;

    rv = sw_uk_exec(SW_API_ACL_PT_UDF_PROFILE_GET, dev_id, port_id, udf_type, (a_uint32_t)offset, (a_uint32_t)length);
    return rv;
}

