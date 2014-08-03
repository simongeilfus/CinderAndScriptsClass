#pragma once

#include <luabind/luabind.hpp>

class lua_State;

namespace lua {
	
	class State {
	public:
		static void create( bool bindAll = true );
		static lua_State* get();
		static void clear();
		~State();
        
	private:
		State();
		static int panic( lua_State *L );
        
		lua_State* mState;
		static State* mInstance;
		bool mBindAll;
	};
    
	class Script {
	public:
		Script( bool bindAll = true, bool useLuaThread = false );
		~Script();
        
		void loadString( const std::string& script );
		void loadFile( ci::DataSourceRef source );
        
		std::string getLastErrors();
        
        void gc();
        
		bool functionExists( const std::string& function );
        
        template<typename T, typename... Args>
        T call( const std::string& function, const Args&... args )
        {
            T result;
            
            if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
                return result;
            
            try{
                result = luabind::call_function<T>( mState, function.c_str(), args... );
                mErrors = false;
            }
            catch( ... ){
                mErrors = true;
                mLastErrorString = getErrorMessage();
                std::cout << "Lua Error trying to call " << function << " : " << std::endl << mLastErrorString << std::endl;
            }
            return result;
        }
        
        
        template<typename... Args>
        void call( const std::string& function, const Args&... args )
        {
            if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
                return;
            
            try{
                // luabind::call_function<void> doesn't seem to catch exception
                // this is a stupid fix...
                void* res = luabind::call_function<void*>( mState, function.c_str(), args... );
                mErrors = false;
            }
            catch( ... ){
                mErrors = true;
                mLastErrorString = getErrorMessage();
                std::cout << "Lua Error trying to call " << function << " : " << std::endl << mLastErrorString << std::endl;
            }
        }
        
        void call2()
        {
           // call( function );
        }
        
        template<typename T>
        T get( std::string name ){
            return luabind::object_cast<T>( luabind::globals( mState )[ name ] );
        }
        
        template<typename T>
        void set( std::string name, T reference ){
            luabind::globals( mState )[ name ] = reference;
        }
        
        lua_State* getState(){ return mState; }

	private:
        static int panic( lua_State* L );
		void addClassSupport();
        
        std::string getErrorMessage();
        
		lua_State*                  mState;

		std::string                 mLastErrorString;
		bool                        mStopOnErrors;
		bool                        mErrors;
	};
};