/*
	SObjectizer 5.
*/

/*!
	\file
	\brief Interface for the dispatcher binders definition.
*/

#pragma once

#include <memory>
#include <functional>

#include <so_5/h/declspec.hpp>
#include <so_5/rt/h/agent.hpp>
#include <so_5/rt/h/disp.hpp>

#include <so_5/rt/h/fwd.hpp>

namespace so_5
{

//
// disp_binding_activator_t
//
/*!
 * \since v.5.4.0
 * \brief Type of activator for agent to dispatcher binding.
 */
using disp_binding_activator_t = std::function< void() >;

//
// disp_binder_t
//

//! Interface for dispatcher binders.
/*!
 * Dispatcher binders are used in the agent registration process to
 * binding of agents to desired dispatchers.
 */
class SO_5_TYPE disp_binder_t
{
	public:
		disp_binder_t();
		virtual ~disp_binder_t();

		//! Allocate resources in dispatcher for new agent.
		virtual disp_binding_activator_t
		bind_agent(
			//! SObjectizer Environment where agent/cooperation/dispatcher
			//! are working.
			environment_t & env,
			//! Agent to be bound.
			agent_ref_t agent_ref ) = 0;

		//! Unbind agent from dispatcher.
		virtual void
		unbind_agent(
			//! SObjectizer Environment where agent/cooperation/dispatcher
			//! are working.
			environment_t & env,
			//! Agent to be bound.
			agent_ref_t agent_ref ) = 0;

};

//! Typedef for the disp_binder autopointer.
using disp_binder_unique_ptr_t = std::unique_ptr< disp_binder_t >;

//! Typedef for the disp_binder smart pointer.
using disp_binder_ref_t = std::shared_ptr< disp_binder_t >;

//! Create an instance of the default dispatcher binding.
SO_5_FUNC disp_binder_unique_ptr_t
create_default_disp_binder();

namespace rt
{

/*!
 * \deprecated Will be removed in v.5.6.0. Use so_5::disp_binding_activator_t
 * instead.
 */
using disp_binding_activator_t = so_5::disp_binding_activator_t;

/*!
 * \deprecated Will be removed in v.5.6.0. Use so_5::disp_binder_t
 * instead.
 */
using disp_binder_t = so_5::disp_binder_t;

/*!
 * \deprecated Will be removed in v.5.6.0. Use so_5::disp_binder_unique_ptr_t
 * instead.
 */
using disp_binder_unique_ptr_t = so_5::disp_binder_unique_ptr_t;

/*!
 * \deprecated Will be removed in v.5.6.0. Use so_5::disp_binder_ref_t
 * instead.
 */
using disp_binder_ref_t = so_5::disp_binder_ref_t;

/*!
 * \deprecated Will be removed in v.5.6.0. Use so_5::create_default_disp_binder
 * instead.
 */
inline disp_binder_unique_ptr_t
create_default_disp_binder()
	{
		return so_5::create_default_disp_binder();
	}

} /* namespace rt */

} /* namespace so_5 */

