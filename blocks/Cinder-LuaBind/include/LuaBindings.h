//
//  LuaBindings.h
//  LuaBindings
//
//  Created by Simon Geilfus on 31/03/13.
//  Copyright (c) 2013 Simon Geilfus. All rights reserved.
//

#pragma once

class lua_State;

namespace lua {
    
	namespace Bindings {
        
		void bindCinder( lua_State* state );
		void bindStd( lua_State* state );
        
	};
    
}

