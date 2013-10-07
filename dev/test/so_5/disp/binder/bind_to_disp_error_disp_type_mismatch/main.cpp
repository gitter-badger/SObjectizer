/*
 * A test of trying to bind agent to dispatcher with different type.
 */

#include <iostream>
#include <exception>
#include <stdexcept>
#include <memory>
#include <map>

#include <ace/Thread_Manager.h>

#include <so_5/rt/h/rt.hpp>
#include <so_5/api/h/api.hpp>

#include <so_5/disp/active_obj/h/pub.hpp>
#include <so_5/disp/active_group/h/pub.hpp>

class test_agent_t
	:
		public so_5::rt::agent_t
{
		typedef so_5::rt::agent_t base_type_t;

	public:
		test_agent_t(
			so_5::rt::so_environment_t & env )
			:
				base_type_t( env )
		{}

		virtual ~test_agent_t()
		{}
};

void
init( so_5::rt::so_environment_t & env )
{
	so_5::rt::agent_coop_unique_ptr_t coop =
		env.create_coop( "test_coop" );

	coop->add_agent(
		new test_agent_t( env ),
		so_5::disp::active_group::create_disp_binder(
			"active_obj",
			"sample_group" ) );

	bool exception_thrown = false;
	try
	{
		env.register_coop( std::move( coop ) );
	}
	catch( const so_5::exception_t & )
	{
		exception_thrown = true;
	}

	if( !exception_thrown )
		throw std::runtime_error( "invalid coop registered" );

	env.stop();
}

int
main( int argc, char * argv[] )
{
	try
	{
		so_5::api::run_so_environment(
			&init,
			so_5::rt::so_environment_params_t()
				.mbox_mutex_pool_size( 2 )
				.agent_event_queue_mutex_pool_size( 2 )
				.add_named_dispatcher(
					so_5::rt::nonempty_name_t( "active_obj" ),
					so_5::disp::active_obj::create_disp() ) );

		// Wait all threads to finish.
		ACE_Thread_Manager::instance()->wait();
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
