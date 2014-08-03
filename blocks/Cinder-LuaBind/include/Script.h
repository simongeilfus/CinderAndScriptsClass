#pragma once

#include <luabind/luabind.hpp>

class lua_State;

namespace lua {
    
    typedef std::shared_ptr<class Script> ScriptRef;
    
	class Script {
	public:
        //! creates a Script
        static ScriptRef create( bool bindAll = true, bool useLuaThread = false );
        //! creates and loads script from DataSourceRef and returns a ScriptRef
        static ScriptRef create( ci::DataSourceRef script, bool bindAll = true, bool useLuaThread = false );
        //! creates and loads script from string and returns a ScriptRef
        static ScriptRef create( const char *script, bool bindAll = true, bool useLuaThread = false );
        
        //! Script destructor
		~Script();
        
        //! loads a script section from a file on disk
        void loadFromFile( ci::DataSourceRef script );
        //! loads a script section from memory
        void loadFromMemory( const std::string &script );
        
        //! returns the last errors if any
		std::string getLastErrors();
        
        //! forces garbage collecting
        void gc();
        
        //! returns wether a function exists or not
		bool functionExists( const std::string &function );
        
        //! calls a scripted function and returns its value
        template<typename... Args>
        void call( const std::string& function, const Args&... args );
        
        //! calls a scripted function and returns its value
        template<typename T, typename... Args>
        T call( const std::string &function, const Args&... args );
        
        //! returns a global variable by its name
        template<typename T>
        T get( const std::string &name );
        
        //! sets a global variable by its name
        template<typename T>
        void set( const std::string &name, T reference );
        
        //! returns the lua_State of the script
        lua_State* getState(){ return mState; }
        
        
	private:
        //! Creates an empty script
        Script( bool bindAll = true, bool useLuaThread = false );
        //! Creates and loads a script from a file
        Script( ci::DataSourceRef script, bool bindAll = true, bool useLuaThread = false );
        //! Creates and loads a script from memory
        Script( const std::string &script, bool bindAll = true, bool useLuaThread = false );
        
        void init( bool bindAll, bool useLuaThread );
        
        static int panic( lua_State* L );
		void addClassSupport();
        
        std::string getErrorMessage();
        
		lua_State*                  mState;

		std::string                 mLastErrorString;
		bool                        mStopOnErrors;
		bool                        mErrors;
	};
    
    
    template<typename... Args>
    void Script::call( const std::string& function, const Args&... args )
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
    
    template<typename T, typename... Args>
    T Script::call( const std::string &function, const Args&... args )
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
    
    
    template<typename T>
    T Script::get( const std::string &name ){
        return luabind::object_cast<T>( luabind::globals( mState )[ name ] );
    }
    
    template<typename T>
    void Script::set( const std::string &name, T reference ){
        luabind::globals( mState )[ name ] = reference;
    }
    
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
};