/**
 *  @file bool_query.c
 *  Implementation of the interface for searching and iterating over booleans.
 *
 *  @author Kevin Carr kcarr@tresys.com
 *  @author Jeremy A. Mowery jmowery@tresys.com
 *  @author Jason Tang jtang@tresys.com
 *
 *  Copyright (C) 2006 Tresys Technology, LLC
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
 
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <sepol/handle.h>
#include <qpol/iterator.h>
#include <sepol/policydb.h>
#include <sepol/policydb/policydb.h>
#include <sepol/policydb/expand.h>
#include "iterator_internal.h"
#include <qpol/bool_query.h>
#include "debug.h"

int qpol_policy_get_bool_by_name(sepol_handle_t *handle, qpol_policy_t *policy, const char *name, qpol_bool_t **datum)
{
	hashtab_datum_t internal_datum;
	policydb_t *db;

	if (handle == NULL || policy == NULL || name == NULL || datum == NULL) {
		if (datum != NULL)
			*datum = NULL;
		ERR(handle, strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}
	
	db = &((sepol_policydb_t*)policy)->p;
	internal_datum = hashtab_search(db->p_bools.table, (const hashtab_key_t)name);
	if (internal_datum == NULL) {
		ERR(handle, "could not find datum for bool %s", name);
		*datum = NULL;
		errno = ENOENT;
		return STATUS_ERR;
	}
	*datum = (qpol_bool_t*)internal_datum;

	return STATUS_SUCCESS;	
}

int qpol_policy_get_bool_iter(sepol_handle_t *handle, qpol_policy_t *policy, qpol_iterator_t **iter)
{
	policydb_t *db;
	hash_state_t *hs = NULL;
	int error = 0;

	if (handle == NULL || policy == NULL || iter == NULL) {
		if (iter != NULL)
			*iter = NULL;
		ERR(handle, strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	db = &((sepol_policydb_t*)policy)->p;

	hs = calloc(1, sizeof(hash_state_t));
	if (hs == NULL) {
		error = errno;
		ERR(handle, "memory error");
		errno = error;
		return STATUS_ERR;
	}
	hs->table = &db->p_bools.table;
	hs->node = (*(hs->table))->htable[0];

	if (qpol_iterator_create(handle, db, (void*)hs, hash_state_get_cur,
		hash_state_next, hash_state_end, hash_state_size, free, iter)) {
		free(hs);
		return STATUS_ERR;
	}

	if (hs->node == NULL)
		hash_state_next(*iter);

	return STATUS_SUCCESS;
}

int qpol_bool_get_value(sepol_handle_t *handle, qpol_policy_t *policy, qpol_bool_t *datum, uint32_t *value)
{
	cond_bool_datum_t *internal_datum;

	if (handle == NULL || policy == NULL || datum == NULL || value == NULL) {
		if (value != NULL)
			*value = 0;
		ERR(handle, strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_datum = (cond_bool_datum_t*)datum;
	*value = internal_datum->value;

	return STATUS_SUCCESS;
}

int qpol_bool_get_state(sepol_handle_t *handle, qpol_policy_t *policy, qpol_bool_t *datum, int *state)
{
	cond_bool_datum_t *internal_datum;

	if (handle == NULL || policy == NULL || datum == NULL || state == NULL) {
		if (state != NULL)
			*state = 0;
		ERR(handle, strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_datum = (cond_bool_datum_t*)datum;
	*state = internal_datum->state;

	return STATUS_SUCCESS;
}

int qpol_bool_set_state(sepol_handle_t *handle, qpol_policy_t *policy, qpol_bool_t *datum, int state)
{
	cond_bool_datum_t *internal_datum;

	if (handle == NULL || policy == NULL || datum == NULL) {
		ERR(handle, strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_datum = (cond_bool_datum_t*)datum;
	internal_datum->state = state;

	return STATUS_SUCCESS;
}

int qpol_bool_get_name(sepol_handle_t *handle, qpol_policy_t *policy, qpol_bool_t *datum, char **name)
{
	cond_bool_datum_t *internal_datum = NULL;
	policydb_t *db = NULL;

	if (handle == NULL ||  policy == NULL || datum == NULL || name == NULL) {
		if (name != NULL)
			*name = NULL;
		ERR(handle, strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	db = &((sepol_policydb_t*)policy)->p;
	internal_datum = (cond_bool_datum_t*)datum;

	*name = db->p_bool_val_to_name[internal_datum->value - 1];

	return STATUS_SUCCESS;
}

 