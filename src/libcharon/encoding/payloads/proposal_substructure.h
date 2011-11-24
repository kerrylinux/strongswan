/*
 * Copyright (C) 2005-2006 Martin Willi
 * Copyright (C) 2005 Jan Hutter
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * @defgroup proposal_substructure proposal_substructure
 * @{ @ingroup payloads
 */

#ifndef PROPOSAL_SUBSTRUCTURE_H_
#define PROPOSAL_SUBSTRUCTURE_H_

typedef struct proposal_substructure_t proposal_substructure_t;

#include <library.h>
#include <encoding/payloads/payload.h>
#include <encoding/payloads/transform_substructure.h>
#include <config/proposal.h>
#include <utils/linked_list.h>
#include <kernel/kernel_ipsec.h>
#include <sa/authenticators/authenticator.h>

/**
 * Class representing an IKEv1/IKEv2 proposal substructure.
 */
struct proposal_substructure_t {

	/**
	 * The payload_t interface.
	 */
	payload_t payload_interface;

	/**
	 * Sets the proposal number of current proposal.
	 *
	 * @param id			proposal number to set
	 */
	void (*set_proposal_number) (proposal_substructure_t *this,
								 u_int8_t proposal_number);
	/**
	 * get proposal number of current proposal.
	 *
	 * @return 			proposal number of current proposal substructure.
	 */
	u_int8_t (*get_proposal_number) (proposal_substructure_t *this);

	/**
	 * Sets the protocol id of current proposal.
	 *
	 * @param id		protocol id to set
	 */
	void (*set_protocol_id) (proposal_substructure_t *this,
							 u_int8_t protocol_id);

	/**
	 * get protocol id of current proposal.
	 *
	 * @return 			protocol id of current proposal substructure.
	 */
	u_int8_t (*get_protocol_id) (proposal_substructure_t *this);

	/**
	 * Sets the next_payload field of this substructure
	 *
	 * If this is the last proposal, next payload field is set to 0,
	 * otherwise to 2
	 *
	 * @param is_last	When TRUE, next payload field is set to 0, otherwise to 2
	 */
	void (*set_is_last_proposal) (proposal_substructure_t *this, bool is_last);

	/**
	 * Returns the currently set SPI of this proposal.
	 *
	 * @return 			chunk_t pointing to the value
	 */
	chunk_t (*get_spi) (proposal_substructure_t *this);

	/**
	 * Sets the SPI of the current proposal.
	 *
	 * @warning SPI is getting copied
	 *
	 * @param spi		chunk_t pointing to the value to set
	 */
	void (*set_spi) (proposal_substructure_t *this, chunk_t spi);

	/**
	 * Get proposals contained in a propsal_substructure_t.
	 *
	 * @param list		list to add created proposals to
	 */
	void (*get_proposals) (proposal_substructure_t *this, linked_list_t *list);

	/**
	 * Create an enumerator over transform substructures.
	 *
	 * @return			enumerator over transform_substructure_t
	 */
	enumerator_t* (*create_substructure_enumerator)(proposal_substructure_t *this);

	/**
	 * Destroys an proposal_substructure_t object.
	 */
	void (*destroy) (proposal_substructure_t *this);
};

/**
 * Creates an empty proposal_substructure_t object
 *
 * @param type		PROPOSAL_SUBSTRUCTURE or PROPOSAL_SUBSTRUCTURE_V1
 * @return			proposal_substructure_t object
 */
proposal_substructure_t *proposal_substructure_create(payload_type_t type);

/**
 * Creates an IKEv2 proposal_substructure_t from a proposal_t.
 *
 * @param proposal	proposal to build a substruct out of it
 * @return 			proposal_substructure_t PROPOSAL_SUBSTRUCTURE
 */
proposal_substructure_t *proposal_substructure_create_from_proposal_v2(
														proposal_t *proposal);
/**
 * Creates an IKEv1 proposal_substructure_t from a proposal_t.
 *
 * @param proposal	proposal to build a substruct out of it
 * @param lifetime	lifetime in seconds
 * @param lifebytes	lifebytes, in bytes
 * @param auth		authentication method to use, or AUTH_NONE
 * @param mode		IPsec encapsulation mode, TRANSPORT or TUNNEL
 * @param udp		TRUE to use UDP encapsulation
 *
 *
 * @return 			proposal_substructure_t object PROPOSAL_SUBSTRUCTURE_V1
 */
proposal_substructure_t *proposal_substructure_create_from_proposal_v1(
			proposal_t *proposal,  u_int32_t lifetime, u_int64_t lifebytes,
			auth_method_t auth, ipsec_mode_t mode, bool udp);

/**
 * Creates an IKEv1 proposal_substructure_t from a list of proposal_t.
 *
 * @param proposals	list of proposal_t to encode in a substructure
 * @param lifetime	lifetime in seconds
 * @param lifebytes	lifebytes, in bytes
 * @param auth		authentication method to use, or AUTH_NONE
 * @param mode		IPsec encapsulation mode, TRANSPORT or TUNNEL
 * @param udp		TRUE to use UDP encapsulation
 * @return 			IKEv1 proposal_substructure_t PROPOSAL_SUBSTRUCTURE_V1
 */
proposal_substructure_t *proposal_substructure_create_from_proposals_v1(
			linked_list_t *proposals, u_int32_t lifetime, u_int64_t lifebytes,
			auth_method_t auth, ipsec_mode_t mode, bool udp);

#endif /** PROPOSAL_SUBSTRUCTURE_H_ @}*/
