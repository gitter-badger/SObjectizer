/*
	SObjectizer 5.
*/

/*!
	\file
	\brief Mbox definition.
*/

#pragma once

#include <string>
#include <memory>
#include <typeindex>
#include <utility>

#include <so_5/h/declspec.hpp>
#include <so_5/h/compiler_features.hpp>

#include <so_5/h/exception.hpp>

#include <so_5/rt/h/mbox_fwd.hpp>
#include <so_5/rt/h/message.hpp>
#include <so_5/rt/h/event_data.hpp>

namespace so_5
{

namespace rt
{

template< class RESULT >
class service_invoke_proxy_t;

/*!
 * \since v.5.3.0
 * \brief A special helper class for infinite waiting of service call.
 */
template< class RESULT >
class infinite_wait_service_invoke_proxy_t
	{
		//! Type of creator of that object.
		typedef service_invoke_proxy_t< RESULT > creator_t;

	public :
		infinite_wait_service_invoke_proxy_t(
			const creator_t & creator );

		//! Make synchronous service request call.
		/*!
		 * This method should be used for the case where PARAM is a signal.
		 *
		 * \tparam PARAM type of signal to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
		 	const so_5::rt::mbox_t & dest = ...;
			std::string result = dest.get_one< std::string >().wait_forever().sync_get< status_signal >();
		 * \endcode
		 */
		template< class PARAM >
		RESULT
		sync_get() const;

		//! Make synchronous service request call with parameter.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
		 	void some_agent::some_event( const so_5::rt::event_data_t< request > & req )
			{
				const so_5::rt::mbox_t & dest = ...;
				std::string result = dest.get_one< std::string >().wait_forever().sync_get( req.make_reference() );
			}
		 * \endcode
		 */
		template< class PARAM >
		RESULT
		sync_get( intrusive_ptr_t< PARAM > msg_ref ) const;

		//! Make synchronous service request call with parameter.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
			const so_5::rt::mbox_t & dest = ...;
			std::string result = dest.get_one< std::string >().wait_forever().sync_get( std::make_unique< request >(...) );
		 * \endcode
		 */
		template< class PARAM >
		RESULT
		sync_get( std::unique_ptr< PARAM > msg_unique_ptr ) const;

		//! Make synchronous service request call with parameter.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
			const so_5::rt::mbox_t & dest = ...;
			std::string result = dest.get_one< std::string >().wait_forever().sync_get( new request(...) );
			\endcode
		 *
		 */
		template< class PARAM >
		RESULT
		sync_get( PARAM * msg ) const;

		//! Create param and make service request call.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 * \tparam ARGS types of PARAM's constructor arguments.
		 *
		 * \par Usage example:
		 * \code
			const so_5::rt::mbox_t & dest = ...;
			std::string result = dest.get_one< std::string >().wait_forever().make_sync_get< request >(...) );
		 * \endcode
		 */
		template< class PARAM, typename... ARGS >
		RESULT
		make_sync_get( ARGS&&... args ) const;

	private :
		const creator_t m_creator;
	};

/*!
 * \since v.5.3.0
 * \brief A special helper class for waiting of service call for
 * the specified timeout.
 */
template< class RESULT, class DURATION >
class wait_for_service_invoke_proxy_t
	{
		//! Type of creator of that object.
		typedef service_invoke_proxy_t< RESULT > creator_t;

	public :
		wait_for_service_invoke_proxy_t(
			const creator_t & creator,
			const DURATION & timeout );

		//! Make synchronous service request call with parameter and
		//! wait timeout.
		/*!
		 * This method should be used for the case where PARAM is a signal.
		 *
		 * \tparam PARAM type of signal to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
		 	const so_5::rt::mbox_t & dest = ...;
			std::string result = dest.get_one< std::string >().wait_for(timeout).sync_get< status_signal >();
		 * \endcode
		 *
		 * \throw so_5::exception_t with error code
		 * so_5::rc_svc_result_not_received_yet if there is no svc_handler result
		 * after timeout.
		 */
		template< class PARAM >
		RESULT
		sync_get() const;

		//! Make synchronous service request call with parameter and
		//! wait timeout.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
		 	void some_agent::some_event( const so_5::rt::event_data_t< request > & req )
			{
				const so_5::rt::mbox_t & dest = ...;
				std::string result = dest.get_one< std::string >().wait_for(timeout).sync_get( req.make_reference() );
			}
		 * \endcode
		 *
		 * \throw so_5::exception_t with error code
		 * so_5::rc_svc_result_not_received_yet if there is no svc_handler result
		 * after timeout.
		 */
		template< class PARAM >
		RESULT
		sync_get( intrusive_ptr_t< PARAM > msg_ref ) const;

		//! Make synchronous service request call with parameter and
		//! wait timeout.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
			const so_5::rt::mbox_t & dest = ...;
			std::string result = dest.get_one< std::string >().wait_for(timeout).sync_get( std::make_unique< request >(...) );
		 * \endcode
		 *
		 * \throw so_5::exception_t with error code
		 * so_5::rc_svc_result_not_received_yet if there is no svc_handler result
		 * after timeout.
		 */
		template< class PARAM >
		RESULT
		sync_get( std::unique_ptr< PARAM > msg_unique_ptr ) const;

		//! Make synchronous service request call with parameter and
		//! wait timeout.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
			const so_5::rt::mbox_t & dest = ...;
			std::string result = dest.get_one< std::string >().wait_for(timeout).sync_get( new request(...) );
			\endcode
		 *
		 * \throw so_5::exception_t with error code
		 * so_5::rc_svc_result_not_received_yet if there is no svc_handler result
		 * after timeout.
		 */
		template< class PARAM >
		RESULT
		sync_get( PARAM * msg ) const;

		//! Create param and make service request call.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 * \tparam ARGS types of PARAM's constructor arguments.
		 *
		 * \par Usage example:
		 	\code
			const so_5::rt::mbox_t & dest = ...;
			std::string result = dest.get_one< std::string >().wait_for(timeout).make_sync_get< request >(...) );
		 	\endcode
		 *
		 * \throw so_5::exception_t with error code
		 * so_5::rc_svc_result_not_received_yet if there is no svc_handler result
		 * after timeout.
		 */
		template< class PARAM, typename... ARGS >
		RESULT
		make_sync_get( ARGS&&... args ) const;

	private :
		const creator_t m_creator;
		const DURATION m_timeout;
	};

/*!
 * \since v.5.3.0
 * \brief A special proxy for service request invocation.
 */
template< class RESULT >
class service_invoke_proxy_t
	{
	public :
		explicit service_invoke_proxy_t( const mbox_t & mbox );
		explicit service_invoke_proxy_t( mbox_t && mbox );

		//! Make asynchronous service request.
		/*!
		 * This method should be used for the cases where PARAM is a signal.
		 *
		 * \tparam PARAM type of signal to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
		 	const so_5::rt::mbox_t & dest = ...;
			std::future< std::string > result = dest.get_one< std::string >().async< status_signal >();
		 * \endcode
		 */
		template< class PARAM >
		std::future< RESULT >
		async() const;

		//! Make service request call with param.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
		 	void some_agent::some_event( const so_5::rt::event_data_t< request > & req )
			{
				const so_5::rt::mbox_t & dest = ...;
				std::future< std::string > result = dest.get_one< std::string >().async( req.make_reference() );
			}
		 * \endcode
		 */
		template< class PARAM >
		std::future< RESULT >
		async( intrusive_ptr_t< PARAM > msg_ref ) const;

		//! Make service request call with param.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
			const so_5::rt::mbox_t & dest = ...;
			std::future< std::string > result = dest.get_one< std::string >().async( std::make_unique< request >(...) );
		 * \endcode
		 */
		template< class PARAM >
		std::future< RESULT >
		async( std::unique_ptr< PARAM > msg_unique_ptr ) const;

		//! Make service request call with param.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 *
		 * \par Usage example:
		 * \code
			const so_5::rt::mbox_t & dest = ...;
			std::future< std::string > result = dest.get_one< std::string >().async( new request(...) );
		 * \endcode
		 */
		template< class PARAM >
		std::future< RESULT >
		async( PARAM * msg ) const;

		//! Make another proxy for time-unlimited synchronous
		//! service request calls.
		/*!
		 * This method is used as second part of method chain for
		 * synchronous interaction. It must be used if service request
		 * initiator want to wait response of infinite amount of time.
		 *
		 * The call to wait_forever if equivalent of:
		 * \code
		 	std::future< Resp > f = mbox.get_one< Resp >().make_async< Req >(...);
			Resp r = f.get();
		 * \endcode
		 *
		 * It means that return conditions for wait_forever() are the same
		 * as return conditions for underlying call to std::future::get().
		 *
		 * \par Usage example:
		 * \code
		 	const so_5::rt::mbox_t & dest = ...;
		 	std::string r = dest.get_one< std::string >().wait_forever().make_sync_get< request >(...);
		 * \endcode
		 */
		infinite_wait_service_invoke_proxy_t< RESULT >
		wait_forever() const;

		//! Make another proxy for time-limited synchronous
		//! service requests calls.
		/*!
		 * This method is used as second part of method chain for
		 * synchronous interaction. It must be used if service request
		 * initiator want to wait response no more than specified amount
		 * of time.
		 *
		 * The call to wait_for if equivalent of:
		 * \code
		 	std::future< Resp > f = mbox.get_one< Resp >().make_async< Req >(...);
			auto wait_result = f.wait_for( timeout );
			if( std::future_status::ready != wait_result )
				throw some_exception();
			Resp r = f.get();
		 * \endcode
		 *
		 * It means that return conditions for wait_for() are the same
		 * as return conditions for underlying call to std::future::wait_for().
		 *
		 * \par Usage example:
		 * \code
		 	const so_5::rt::mbox_t & dest = ...;
		 	std::string r = dest.get_one< std::string >().wait_for(std::chrono::milliseconds(50)).make_sync_get< request >(...);
		 * \endcode
		 */
		template< class DURATION >
		wait_for_service_invoke_proxy_t< RESULT, DURATION >
		wait_for(
			//! Timeout for std::future::wait_for().
			const DURATION & timeout ) const;

		//! Create param and make service request call.
		/*!
		 * This method should be used for the case where PARAM is a message.
		 *
		 * \tparam PARAM type of message to be sent to distination.
		 * \tparam ARGS types of PARAM's constructor arguments.
		 *
		 * \par Usage example:
		 * \code
			const so_5::rt::mbox_t & dest = ...;
			std::future< std::string > result = dest.get_one< std::string >().make_async< request >(...) );
		 * \endcode
		 */
		template< class PARAM, typename... ARGS >
		std::future< RESULT >
		make_async( ARGS&&... args ) const;

	private :
		mbox_t m_mbox;
	};

//
// delivery_filter_t
//
/*!
 * \since v.5.5.5
 * \brief An interface of delivery filter object.
 */
class SO_5_TYPE delivery_filter_t
	{
	public :
		virtual ~delivery_filter_t();

		//! Checker for a message instance.
		/*!
		 * \retval true message must be delivered to a receiver.
		 * \retval false message must be descarded.
		 */
		virtual bool
		check(
			//! Receiver of the message.
			const agent_t & receiver,
			//! Message itself.
			const message_t & msg ) const SO_5_NOEXCEPT = 0;
	};

//
// delivery_filter_unique_ptr_t
//
/*!
 * \since v.5.5.5
 * \brief An alias of unique_ptr for delivery_filter.
 */
using delivery_filter_unique_ptr_t =
	std::unique_ptr< delivery_filter_t >;

//
// mbox_type_t
//
/*!
 * \since v.5.5.3
 * \brief Type of the message box.
 */
enum class mbox_type_t
	{
		//! Mbox is Multi-Producer and Multi-Consumer.
		//! Anyone can send messages to it, there can be many subscribers.
		multi_producer_multi_consumer,
		//! Mbox is Multi-Producer and Single-Consumer.
		//! Anyone can send messages to it, there can be only one subscriber.
		multi_producer_single_consumer
	};

//
// abstract_message_box_t
//

//! Mail box class.
/*!
 * The class serves as an interface for sending and receiving messages.
 *
 * All mboxes can be created via the SObjectizer Environment. References to
 * mboxes are stored and manipulated by so_5::rt::mbox_t objects.
 *
 * abstract_message_box_t has two versions of the deliver_message() method. 
 * The first one requires pointer to the actual message data and is intended 
 * for delivering messages to agents.
 * The second one doesn't use a pointer to the actual message data and 
 * is intended for delivering signals to agents.
 *
 * abstract_message_box_t also is used for the delivery of delayed and periodic
 * messages.  The SObjectizer Environment stores mbox for which messages must
 * be delivered and the timer thread pushes message instances to the mbox at
 * the appropriate time.
 *
 * \see environment_t::schedule_timer(), environment_t::single_timer().
 */
class SO_5_TYPE abstract_message_box_t : private atomic_refcounted_t
{
		friend class intrusive_ptr_t< abstract_message_box_t >;

		abstract_message_box_t( const abstract_message_box_t & );
		void
		operator = ( const abstract_message_box_t & );

	public:
		abstract_message_box_t();
		virtual ~abstract_message_box_t();

		/*!
		 * \since v.5.4.0
		 * \brief Unique ID of this mbox.
		 */
		virtual mbox_id_t
		id() const = 0;

		//! Deliver message.
		/*!
		 * \since v.5.2.2
		 *
		 * Mbox takes care about destroying a message object.
		 */
		template< class MESSAGE >
		inline void
		deliver_message(
			//! Message data.
			const intrusive_ptr_t< MESSAGE > & msg_ref ) const;

		//! Deliver message.
		/*!
		 * Mbox takes care about destroying a message object.
		 */
		template< class MESSAGE >
		inline void
		deliver_message(
			//! Message data.
			std::unique_ptr< MESSAGE > msg_unique_ptr ) const;

		//! Deliver message.
		/*!
		 * Mbox takes care about destroying a message object.
		 */
		template< class MESSAGE >
		inline void
		deliver_message(
			//! Message data.
			MESSAGE * msg_raw_ptr ) const;

		//! Deliver signal.
		template< class MESSAGE >
		inline void
		deliver_signal() const;

		/*!
		 * \since v.5.3.0
		 * \brief Create a special proxy for service request invocation.
		 *
		 * \tparam RESULT type of result to be received as result of
		 * service request.
		 *
		 * \note That method starts methods call chain for synchonous
		 * agents interaction. Next method should be either
		 * wait_forever()/wait_for() or async()/make_async().
		 *
		 * \par Usage examples
		 * \code
		 	// Make synchronous call and acquire result as a future object.
			const so_5::rt::mbox_t & dest = ...;
			std::future< std::string > result =
					dest.get_one< std::string >().make_async< request >(...);

			// Or if request object is already created:
			std::unique_ptr< request > req = std::make_unique< request >(...);
			...
			std::future< std::string > result =
					dest.get_one< std::string >().async( std::move( request ) );

			// Make synchronous call, wait for result indefinitely.
			std::string result =
					dest.get_one< std::string >().wait_forever().make_sync_get< request >(...);
			// Or...
			std::unique_ptr< request > req = std::make_unique< request >(...);
			std::string result =
					dest.get_one< std::string >().wait_forever().sync_get( std::move( request ) );

			// Make synchronous call, wait no more than 50ms.
			std::string result =
					dest.get_one< std::string >().wait_for( std::chrono::milliseconds(50) ).make_sync_get< request >(...);
			// Or...
			std::unique_ptr< request > req = std::make_unique< request >(...);
			std::string result =
					dest.get_one< std::string >().wait_for( std::chrono::milliseconds(50) ).sync_get( std::move( request ) );
		 * \endcode
		 */
		template< class RESULT >
		inline service_invoke_proxy_t< RESULT >
		get_one()
			{
				return service_invoke_proxy_t< RESULT >(
						mbox_t( this ) );
			}

		/*!
		 * \since v.5.3.0
		 * \brief Create a special proxy for service request invocation
		 * where return type is void.
		 *
		 * \tparam RESULT type of result to be received as result of
		 * service request.
		 *
		 * \note This method could useful for waiting a completion of
		 * some message processing by destination agent.
		 *
		 * \sa get_one().
		 */
		inline service_invoke_proxy_t< void >
		run_one()
			{
				return service_invoke_proxy_t< void >( mbox_t( this ) );
			}

		//! Deliver message for all subscribers.
		/*!
		 * \note This method is public since v.5.4.0.
		 *
		 * \note This is a just a wrapper for do_deliver_message
		 * since v.5.5.4.
		 */
		inline void
		deliver_message(
			const std::type_index & msg_type,
			const message_ref_t & message ) const
			{
				this->do_deliver_message( msg_type, message, 1 );
			}

		/*!
		 * \since v.5.3.0.
		 * \brief Deliver service request.
		 *
		 * \note This is a just a wrapper for do_deliver_service_request
		 * since v.5.5.4.
		 */
		inline void
		deliver_service_request(
			//! This is type_index for service PARAM type.
			const std::type_index & msg_type,
			//! This is reference to msg_service_request_t<RESULT,PARAM> instance.
			const message_ref_t & message ) const
			{
				this->do_deliver_service_request( msg_type, message, 1 );
			}

		//! Add the message handler.
		virtual void
		subscribe_event_handler(
			//! Message type.
			const std::type_index & type_index,
			//! Optional message limit for that message type.
			const message_limit::control_block_t * limit,
			//! Agent-subcriber.
			agent_t * subscriber ) = 0;

		//! Remove all message handlers.
		virtual void
		unsubscribe_event_handlers(
			//! Message type.
			const std::type_index & type_index,
			//! Agent-subcriber.
			agent_t * subscriber ) = 0;

		//! Get the mbox name.
		virtual std::string
		query_name() const = 0;

		/*!
		 * \since v.5.5.3
		 * \brief Get the type of message box.
		 *
		 * \note This method is primarily intended for internal usage.
		 * It is useful sometimes in subscription-related operations
		 * because there is no need to do some actions for MPSC mboxes.
		 */
		virtual mbox_type_t
		type() const = 0;

		/*!
		 * \name Comparision.
		 * \{
		 */
		bool operator==( const abstract_message_box_t & o ) const;

		bool operator<( const abstract_message_box_t & o ) const;
		/*!
		 * \}
		 */

		/*!
		 * \since v.5.5.4
		 * \brief Deliver message for all subscribers with respect to message
		 * limits.
		 */
		virtual void
		do_deliver_message(
			//! Type of the message to deliver.
			const std::type_index & msg_type,
			//! A message instance to be delivered.
			const message_ref_t & message,
			//! Current deep of overlimit reaction recursion.
			unsigned int overlimit_reaction_deep ) const = 0;

		/*!
		 * \since v.5.5.4
		 * \brief Deliver service request.
		 */
		virtual void
		do_deliver_service_request(
			//! This is type_index for service PARAM type.
			const std::type_index & msg_type,
			//! This is reference to msg_service_request_t<RESULT,PARAM> instance.
			const message_ref_t & message,
			//! Current deep of overlimit reaction recursion.
			unsigned int overlimit_reaction_deep ) const = 0;

		/*!
		 * \name Methods for working with delivery filters.
		 * \{
		 */
		/*!
		 * \since v.5.5.5
		 * \brief Set a delivery filter for message type and subscriber.
		 *
		 * \note If there already is a delivery filter for that
		 * (msg_type,subscriber) pair then old delivery filter will
		 * be replaced by new one.
		 */
		virtual void
		set_delivery_filter(
			//! Message type to be filtered.
			const std::type_index & msg_type,
			//! Filter to be set.
			//! A caller must guaranted the validity of this reference.
			const delivery_filter_t & filter,
			//! A subscriber for the message.
			agent_t & subscriber ) = 0;

		/*!
		 * \since v.5.5.5
		 * \brief Removes delivery filter for message type and subscriber.
		 */
		virtual void
		drop_delivery_filter(
			const std::type_index & msg_type,
			agent_t & subscriber ) SO_5_NOEXCEPT = 0;
		/*!
		 * \}
		 */
};

template< class MESSAGE >
inline void
abstract_message_box_t::deliver_message(
	const intrusive_ptr_t< MESSAGE > & msg_ref ) const
{
	ensure_message_with_actual_data( msg_ref.get() );

	deliver_message(
		std::type_index( typeid( MESSAGE ) ),
		msg_ref.template make_reference< message_t >() );
}

template< class MESSAGE >
void
abstract_message_box_t::deliver_message(
	std::unique_ptr< MESSAGE > msg_unique_ptr ) const
{
	ensure_message_with_actual_data( msg_unique_ptr.get() );

	deliver_message(
		std::type_index( typeid( MESSAGE ) ),
		message_ref_t( msg_unique_ptr.release() ) );
}

template< class MESSAGE >
void
abstract_message_box_t::deliver_message(
	MESSAGE * msg_raw_ptr ) const
{
	this->deliver_message( std::unique_ptr< MESSAGE >( msg_raw_ptr ) );
}

template< class MESSAGE >
void
abstract_message_box_t::deliver_signal() const
{
	ensure_signal< MESSAGE >();

	deliver_message(
		std::type_index( typeid( MESSAGE ) ),
		message_ref_t() );
}

//
// service_invoke_proxy_t implementation.
//
template< class RESULT >
service_invoke_proxy_t<RESULT>::service_invoke_proxy_t(
	const mbox_t & mbox )
	:	m_mbox( mbox )
	{}

template< class RESULT >
service_invoke_proxy_t<RESULT>::service_invoke_proxy_t(
	mbox_t && mbox )
	:	m_mbox( std::move(mbox) )
	{}

template< class RESULT >
template< class PARAM >
std::future< RESULT >
service_invoke_proxy_t<RESULT>::async() const
	{
		ensure_signal< PARAM >();

		std::promise< RESULT > promise;
		auto f = promise.get_future();

		message_ref_t ref(
				new msg_service_request_t< RESULT, PARAM >(
						std::move(promise) ) );
		m_mbox->deliver_service_request(
				std::type_index( typeid(PARAM) ),
				ref );

		return f;
	}

template< class RESULT >
template< class PARAM >
std::future< RESULT >
service_invoke_proxy_t<RESULT>::async(
	intrusive_ptr_t< PARAM > msg_ref ) const
	{
		ensure_message_with_actual_data( msg_ref.get() );

		std::promise< RESULT > promise;
		auto f = promise.get_future();

		message_ref_t ref(
				new msg_service_request_t< RESULT, PARAM >(
						std::move(promise),
						msg_ref.template make_reference< message_t >() ) );

		m_mbox->deliver_service_request(
				std::type_index( typeid(PARAM) ),
				ref );

		return f;
	}

template< class RESULT >
template< class PARAM >
std::future< RESULT >
service_invoke_proxy_t<RESULT>::async(
	std::unique_ptr< PARAM > msg_unique_ptr ) const
	{
		return this->async( intrusive_ptr_t< PARAM >(
					msg_unique_ptr.release() ) );
	}

template< class RESULT >
template< class PARAM >
std::future< RESULT >
service_invoke_proxy_t<RESULT>::async( PARAM * msg ) const
	{
		return this->async( intrusive_ptr_t< PARAM >( msg ) );
	}

template< class RESULT >
infinite_wait_service_invoke_proxy_t< RESULT >
service_invoke_proxy_t<RESULT>::wait_forever() const
	{
		return infinite_wait_service_invoke_proxy_t< RESULT >( *this );
	}

template< class RESULT >
template< class DURATION >
wait_for_service_invoke_proxy_t< RESULT, DURATION >
service_invoke_proxy_t<RESULT>::wait_for(
	const DURATION & timeout ) const
	{
		return wait_for_service_invoke_proxy_t< RESULT, DURATION >(
				*this, timeout );
	}

template< class RESULT >
template< class PARAM, typename... ARGS >
std::future< RESULT >
service_invoke_proxy_t<RESULT>::make_async( ARGS&&... args ) const
	{
		intrusive_ptr_t< PARAM > msg(
				new PARAM( std::forward<ARGS>(args)... ) );

		return this->async( std::move( msg ) );
	}

//
// implementation of infinite_wait_service_invoke_proxy_t
//

template< class RESULT >
infinite_wait_service_invoke_proxy_t< RESULT >::
infinite_wait_service_invoke_proxy_t(
	const creator_t & creator )
	:	m_creator( creator )
	{}

template< class RESULT >
template< class PARAM >
RESULT
infinite_wait_service_invoke_proxy_t< RESULT >::sync_get() const
	{
		return m_creator.template async< PARAM >().get();
	}

template< class RESULT >
template< class PARAM >
RESULT
infinite_wait_service_invoke_proxy_t< RESULT >::sync_get(
	intrusive_ptr_t< PARAM > msg_ref ) const
	{
		return m_creator.async( std::move(msg_ref) ).get();
	}

template< class RESULT >
template< class PARAM >
RESULT
infinite_wait_service_invoke_proxy_t< RESULT >::sync_get(
	std::unique_ptr< PARAM > msg_unique_ptr ) const
	{
		return this->sync_get(
				intrusive_ptr_t< PARAM >( msg_unique_ptr.release() ) );
	}

template< class RESULT >
template< class PARAM >
RESULT
infinite_wait_service_invoke_proxy_t< RESULT >::sync_get( PARAM * msg ) const
	{
		return this->sync_get(
				intrusive_ptr_t< PARAM >( msg ) );
	}

template< class RESULT >
template< class PARAM, typename... ARGS >
RESULT
infinite_wait_service_invoke_proxy_t< RESULT >::make_sync_get(
	ARGS&&... args ) const
	{
		return m_creator.template make_async< PARAM, ARGS... >(
				std::forward<ARGS>(args)... ).get();
	}

//
// implemetation of wait_for_service_invoke_proxy_t
//
template< class RESULT, class DURATION >
wait_for_service_invoke_proxy_t< RESULT, DURATION >::wait_for_service_invoke_proxy_t(
	const creator_t & creator,
	const DURATION & timeout )
	:	m_creator( creator )
	,	m_timeout( timeout )
	{}

/*!
 * \brief Helper functions for implementation of %wait_for_service_invoke_proxy_t class.
 */
namespace wait_for_service_invoke_proxy_details
{
	template< class RESULT, class DURATION, class FUTURE >
	RESULT
	wait_and_return( const DURATION & timeout, FUTURE & f )
		{
#if defined( SO_5_STD_FUTURE_WAIT_FOR_ALWAYS_DEFFERED )
	#pragma message("THERE IS ERROR IN MSVC 11.0: std::future::wait_for returns std::future_status::deffered almost always")
#endif
			auto wait_result = f.wait_for( timeout );
			if( std::future_status::ready != wait_result )
				SO_5_THROW_EXCEPTION(
						rc_svc_result_not_received_yet,
						"no result from svc_handler after timeout" );
			
			return f.get();
		}

} /* namespace wait_for_service_invoke_proxy_details */

template< class RESULT, class DURATION >
template< class PARAM >
RESULT
wait_for_service_invoke_proxy_t< RESULT, DURATION >::sync_get() const
	{
		auto f = m_creator.template async< PARAM >();

		return wait_for_service_invoke_proxy_details::wait_and_return
				<RESULT, DURATION, decltype(f) >( m_timeout, f );
	}

template< class RESULT, class DURATION >
template< class PARAM >
RESULT
wait_for_service_invoke_proxy_t< RESULT, DURATION >::sync_get(
	intrusive_ptr_t< PARAM > msg_ref ) const
	{
		auto f = m_creator.async( std::move(msg_ref) );

		return wait_for_service_invoke_proxy_details::wait_and_return
				<RESULT, DURATION, decltype(f) >( m_timeout, f );
	}

template< class RESULT, class DURATION >
template< class PARAM >
RESULT
wait_for_service_invoke_proxy_t< RESULT, DURATION >::sync_get(
	std::unique_ptr< PARAM > msg_unique_ptr ) const
	{
		return this->sync_get(
				intrusive_ptr_t< PARAM >(
						msg_unique_ptr.release() ) );
	}

template< class RESULT, class DURATION >
template< class PARAM >
RESULT
wait_for_service_invoke_proxy_t< RESULT, DURATION >::sync_get(
	PARAM * msg ) const
	{
		return this->sync_get(
				intrusive_ptr_t< PARAM >( msg ) );
	}

template< class RESULT, class DURATION >
template< class PARAM, typename... ARGS >
RESULT
wait_for_service_invoke_proxy_t< RESULT, DURATION >::make_sync_get(
	ARGS&&... args ) const
	{
		intrusive_ptr_t< PARAM > msg(
				new PARAM( std::forward<ARGS>(args)... ) );

		return this->sync_get( std::move( msg ) );
	}

} /* namespace rt */

} /* namespace so_5 */

