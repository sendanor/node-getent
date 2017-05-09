/* Node.js Crypt(3) implementation */


#include <sys/types.h> // for getpwent, setpwent, endpwent
#include <pwd.h>
#include <grp.h>

#include <errno.h> // for errno
#include <string.h> // for strerror

#include <nan.h>

using namespace Nan; 
using namespace v8;
using std::string;
using std::vector;


/* 
* Binding for getpwent
* The getpwent() function returns a pointer to a structure containing the broken-out fields of a record from the password database 
* (e.g., the local password file /etc/passwd, NIS, and LDAP). 
* The first time getpwent() is called, it returns the first entry; thereafter, it returns successive entries.
*/

NAN_METHOD (getpwentMethod) {

	struct passwd *tmp;
	int err;
	errno = 0;
	tmp = getpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		Nan::ThrowError(Nan::New<v8::String>(strerror(err)).ToLocalChecked());
	}else if(tmp == NULL) {
	    info.GetReturnValue().Set(Nan::Undefined());
	}else{
		// Return the data as an object
		v8::Local<v8::Object> obj = Nan::New<v8::Object>();
		Nan::Set(obj, Nan::New<v8::String>("name").ToLocalChecked(),Nan::New<v8::String>(tmp->pw_name).ToLocalChecked());
		Nan::Set(obj, Nan::New<v8::String>("name").ToLocalChecked(),Nan::New<v8::String>(tmp->pw_name).ToLocalChecked());
		Nan::Set(obj, Nan::New<v8::String>("passwd").ToLocalChecked(),Nan::New<v8::String>(tmp->pw_passwd).ToLocalChecked());
		Nan::Set(obj, Nan::New<v8::String>("uid").ToLocalChecked(),Nan::New<v8::Number>(tmp->pw_uid));
		Nan::Set(obj, Nan::New<v8::String>("gid").ToLocalChecked(),Nan::New<v8::Number>(tmp->pw_gid));
		Nan::Set(obj, Nan::New<v8::String>("gecos").ToLocalChecked(),Nan::New<v8::String>(tmp->pw_gecos).ToLocalChecked());
		Nan::Set(obj, Nan::New<v8::String>("dir").ToLocalChecked(),Nan::New<v8::String>(tmp->pw_dir).ToLocalChecked());
		Nan::Set(obj, Nan::New<v8::String>("shell").ToLocalChecked(),Nan::New<v8::String>(tmp->pw_shell).ToLocalChecked());
		info.GetReturnValue().Set(obj);
	}

}    	

/* 
* Binding for setpwent 
* The setpwent() function rewinds to the beginning of the password database. 
*/
NAN_METHOD (setpwentMethod) {

	int err;
	errno = 0;
	setpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		Nan::ThrowError(Nan::New<v8::String>(strerror(err)).ToLocalChecked());
	}
	
	info.GetReturnValue().Set(Nan::Undefined());
	
}

/* 
* Binding for endpwent 
* The endpwent() function is used to close the password database after all processing has been performed.
*/
NAN_METHOD (endpwentMethod) {

	int err;
	errno = 0;
	endpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		Nan::ThrowError(Nan::New<v8::String>(strerror(err)).ToLocalChecked());
	}else{
		info.GetReturnValue().Set(Nan::Undefined());
	}

}


/* 
* Binding for getgrent 
* The getgrent() function returns a pointer to a structure containing the broken-out fields of a record in the group database 
* (e.g., the local group file /etc/group, NIS, and LDAP). 
* The first time getgrent() is called, it returns the first entry; thereafter, it returns successive entries.
*/
NAN_METHOD (getgrentMethod) {
	struct group *tmp;
	int err;
	char** mem_tmp;
	int i;

	errno = 0;
	tmp = getgrent();
	err = errno;

	// Check for errors
	if(err != 0) {
		Nan::ThrowError(Nan::New<v8::String>(strerror(err)).ToLocalChecked());
	}else if(tmp == NULL) {// Check for end of data
		info.GetReturnValue().Set(Nan::Undefined());
	}else{

		// Return the data as an object
		v8::Local<v8::Object> obj = Nan::New<v8::Object>();
		v8::Local<v8::Array> members = Nan::New<v8::Array>();

		i = 0;
		for(mem_tmp = tmp->gr_mem; *mem_tmp; ++mem_tmp) {
			Nan::Set(members,i,Nan::New<v8::String>(*mem_tmp).ToLocalChecked());
			i++;
		}

		Nan::Set(obj, Nan::New<v8::String>("name").ToLocalChecked(),Nan::New<v8::String>(tmp->gr_name).ToLocalChecked());
		Nan::Set(obj, Nan::New<v8::String>("passwd").ToLocalChecked(),Nan::New<v8::String>(tmp->gr_passwd).ToLocalChecked());
		Nan::Set(obj, Nan::New<v8::String>("gid").ToLocalChecked(),Nan::New<v8::Number>(tmp->gr_gid));
		Nan::Set(obj, Nan::New<v8::String>("members").ToLocalChecked(),members);
		info.GetReturnValue().Set(obj);
	}
}

/* 
* Binding for setgrent 
* The setgrent() function rewinds to the beginning of the group database, to allow repeated scans.
*/
NAN_METHOD (setgrentMethod) {
	int err;
	errno = 0;
	setgrent();
	err = errno;

	// Check for errors
	if(err != 0) {
		Nan::ThrowError(Nan::New<v8::String>(strerror(err)).ToLocalChecked());
	}else{
		info.GetReturnValue().Set(Nan::Undefined());
	}
}

/* 
* Binding for endgrent 
* The endgrent() function is used to close the group database after all processing has been performed.
*/
NAN_METHOD (endgrentMethod) {
	int err;
	errno = 0;
	endgrent();
	err = errno;

	// Check for errors
	if(err != 0) {
		Nan::ThrowError(Nan::New<v8::String>(strerror(err)).ToLocalChecked());
	}else{
		info.GetReturnValue().Set(Nan::Undefined());
	}
}

NAN_MODULE_INIT(Init) {
  Export(target, "getpwent",getpwentMethod);
  Export(target, "setpwent", setpwentMethod);
  Export(target, "endpwent",endpwentMethod);

  Export(target, "getgrent",getgrentMethod);
  Export(target, "setgrent", setgrentMethod);
  Export(target, "endgrent",endgrentMethod);

}

NODE_MODULE(getent, Init)

/* EOF */
