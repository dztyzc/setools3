/**
 *  @file
 *  Public interface for a single AVC log message.  This is a subclass
 *  of seaudit_message.
 *
 *  @author Jeremy A. Mowery jmowery@tresys.com
 *  @author Jason Tang jtang@tresys.com
 *
 *  Copyright (C) 2006-2007 Tresys Technology, LLC
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

#ifndef SEAUDIT_AVC_MESSAGE_H
#define SEAUDIT_AVC_MESSAGE_H

#include <apol/vector.h>

#ifdef  __cplusplus
extern "C"
{
#endif

	typedef struct seaudit_avc_message seaudit_avc_message_t;

/**
 * AVC messages may be either a granted (i.e., an allow) or a denied.
 */
	typedef enum seaudit_avc_message_type
	{
		SEAUDIT_AVC_UNKNOWN = 0,
		SEAUDIT_AVC_DENIED,
		SEAUDIT_AVC_GRANTED
	} seaudit_avc_message_type_e;

/**
 * Return the type of avc message this is, either a granted (i.e., an
 * allow) or a denied.
 *
 * @param avc AVC message to check.
 *
 * @return AVC message type, or SEAUDIT_AVC_UNKNOWN upon error or if unknown.
 */
	extern seaudit_avc_message_type_e seaudit_avc_message_get_message_type(seaudit_avc_message_t * avc);

/**
 * Return the source context's user of an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Source user, or NULL upon error or if unknown.  Do not
 * free() this string.
 */
	extern char *seaudit_avc_message_get_source_user(seaudit_avc_message_t * avc);

/**
 * Return the source context's role of an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Source role, or NULL upon error or if unknown.  Do not
 * free() this string.
 */
	extern char *seaudit_avc_message_get_source_role(seaudit_avc_message_t * avc);

/**
 * Return the source context's target of an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Source target, or NULL upon error or if unknown.  Do not
 * free() this string.
 */
	extern char *seaudit_avc_message_get_source_type(seaudit_avc_message_t * avc);

/**
 * Return the target context's user of an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Target user, or NULL upon error or if unknown.  Do not
 * free() this string.
 */
	extern char *seaudit_avc_message_get_target_user(seaudit_avc_message_t * avc);

/**
 * Return the target context's role of an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Target role, or NULL upon error or if unknown.  Do not
 * free() this string.
 */
	extern char *seaudit_avc_message_get_target_role(seaudit_avc_message_t * avc);

/**
 * Return the target context's target of an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Target type, or NULL upon error or if unknown.  Do not
 * free() this string.
 */
	extern char *seaudit_avc_message_get_target_type(seaudit_avc_message_t * avc);

/**
 * Return the object class from an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Object class, or NULL upon error or if unknown.  Do not
 * free() this string.
 */
	extern char *seaudit_avc_message_get_object_class(seaudit_avc_message_t * avc);

/**
 * Return a vector of permissions (type char *) from an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Vector of permission strings, or NULL upon error or if
 * unknown.  Do not modify the vector in any way.
 */
	extern apol_vector_t *seaudit_avc_message_get_perm(seaudit_avc_message_t * avc);

/**
 * Return the executable and path from an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Executable string, or NULL upon error or if unknown.  Do
 * not free() this string.
 */
	extern char *seaudit_avc_message_get_exe(seaudit_avc_message_t * avc);

/**
 * Return the command from an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Command, or NULL upon error or if unknown.  Do not free()
 * this string.
 */
	extern char *seaudit_avc_message_get_comm(seaudit_avc_message_t * avc);

/**
 * Return the process ID from an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Process's PID, or 0 upon error or if unknown.
 */
	extern unsigned int seaudit_avc_message_get_pid(seaudit_avc_message_t * avc);

/**
 * Return the inode from an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Process's PID, or 0 upon error or if unknown.
 */
	extern unsigned long seaudit_avc_message_get_inode(seaudit_avc_message_t * avc);

/**
 * Return the path of the object from an avc message.
 *
 * @param avc AVC message to check.
 *
 * @return Object's path, or NULL upon error or if unknown.  Do not
 * free() this string.
 */
	extern char *seaudit_avc_message_get_path(seaudit_avc_message_t * avc);

#ifdef  __cplusplus
}
#endif

#endif