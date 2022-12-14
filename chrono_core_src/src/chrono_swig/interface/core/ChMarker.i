%{
#include "chrono/physics/ChMarker.h"
#include "chrono/physics/ChBody.h"
%}

%shared_ptr(chrono::ChMarker)

#ifdef SWIGPYTHON  // --------------------------------------------------------------------- PYTHON

// Forward ref 
//%import "ChPhysicsItem.i" // parent class does not need %import if all .i are included in proper order
// For some strange reason, the forward reference in the .h must be replicated here:
class chrono::ChBody;

%ignore chrono::ChMarker::GetBody;
%rename(GetBody) chrono::ChMarker::getBodySP;

#endif             // --------------------------------------------------------------------- PYTHON

// Parse the header file to generate wrappers
%include "../../../chrono/physics/ChMarker.h"  

#ifdef SWIGPYTHON  // --------------------------------------------------------------------- PYTHON

// A method is added to ChMarker to return a shared_ptr instead of a raw ptr. 
// The method is renamed so that nothing changes from a user perspective

%extend chrono::ChMarker{
		public:
			std::shared_ptr<chrono::ChBody> getBodySP() const {
				chrono::ChBody* rawptr = $self->GetBody();
				std::shared_ptr<chrono::ChBody> sptr(rawptr);
				return sptr;
				}
			
		};

#endif             // --------------------------------------------------------------------- PYTHON
