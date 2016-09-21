/* Node.js Crypt(3) implementation */

#include <node.h>
#include <v8.h>

#include <sys/types.h> // for getpwent, setpwent, endpwent
#include <pwd.h>
#include <grp.h>

#include <errno.h> // for errno
#include <string.h> // for strerror

using namespace v8;


/* 
* Binding for getpwent
* The getpwent() function returns a pointer to a structure containing the broken-out fields of a record from the password database 
* (e.g., the local password file /etc/passwd, NIS, and LDAP). 
* The first time getpwent() is called, it returns the first entry; thereafter, it returns successive entries.
*/
void getpwentMethod(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	struct passwd *tmp;
	int err;
	errno = 0;
	tmp = getpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, strerror(err))));
    return;
	}

	// // Check for end of data
	if(tmp == NULL) {
		return;
	}

	// Return the data as an object
	Local<Object> obj = Object::New(isolate);

	obj->Set(String::NewFromUtf8(isolate, "name"),   String::NewFromUtf8(isolate,tmp->pw_name));
	obj->Set(String::NewFromUtf8(isolate, "passwd"),String::NewFromUtf8(isolate,tmp->pw_passwd));
	obj->Set(String::NewFromUtf8(isolate, "uid"),   Number::New(isolate,tmp->pw_uid));
	obj->Set(String::NewFromUtf8(isolate, "gid"),   Number::New(isolate,tmp->pw_gid));
	obj->Set(String::NewFromUtf8(isolate, "gecos"), String::NewFromUtf8(isolate,tmp->pw_gecos));
	obj->Set(String::NewFromUtf8(isolate, "dir"),   String::NewFromUtf8(isolate,tmp->pw_dir));
	obj->Set(String::NewFromUtf8(isolate, "shell"), String::NewFromUtf8(isolate,tmp->pw_shell));
	args.GetReturnValue().Set(obj);
}

/* 
* Binding for setpwent 
* The setpwent() function rewinds to the beginning of the password database. 
*/
void setpwentMethod(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	int err;
	errno = 0;
	setpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, strerror(err))));
    	return;
	}
}

/* 
* Binding for endpwent 
* The endpwent() function is used to close the password database after all processing has been performed.
*/
void endpwentMethod(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int err;
	errno = 0;
	endpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, strerror(err))));
    	return;
	}

	return;
}


/* 
* Binding for getgrent 
* The getgrent() function returns a pointer to a structure containing the broken-out fields of a record in the group database 
* (e.g., the local group file /etc/group, NIS, and LDAP). 
* The first time getgrent() is called, it returns the first entry; thereafter, it returns successive entries.
*/
void getgrentMethod(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	struct group *tmp;
	int err;
	// char** mem_tmp;
	// int i;

	errno = 0;
	tmp = getgrent();
	err = errno;

	// Check for errors
	if(err != 0) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,strerror(err))));
	}

	// Check for end of data
	if(tmp == NULL) {
		return;
	}

	// Return the data as an object
	Local<Object> obj = Object::New(isolate);

	// Local<Array> members = Array::New();

	// i = 0;
	// for(mem_tmp = tmp->gr_mem; *mem_tmp; ++mem_tmp) {
	// 	members->Set(i, String::New(*mem_tmp));
	// }
	obj->Set(String::NewFromUtf8(isolate, "name"),   String::NewFromUtf8(isolate,tmp->gr_name));
	obj->Set(String::NewFromUtf8(isolate, "passwd"), String::NewFromUtf8(isolate,tmp->gr_passwd));
	obj->Set(String::NewFromUtf8(isolate, "gid"),    Number::New(isolate,tmp->gr_gid));
	// obj->Set(String::NewSymbol("members"), members);
	args.GetReturnValue().Set(obj);
}

/* 
* Binding for setgrent 
* The setgrent() function rewinds to the beginning of the group database, to allow repeated scans.
*/
void setgrentMethod(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int err;
	errno = 0;
	setgrent();
	err = errno;

	// Check for errors
	if(err != 0) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,strerror(err))));
	}
}

/* 
* Binding for endgrent 
* The endgrent() function is used to close the group database after all processing has been performed.
*/
void endgrentMethod(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	int err;
	errno = 0;
	endgrent();
	err = errno;

	// Check for errors
	if(err != 0) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,strerror(err))));
	}
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "getpwent", getpwentMethod);
  NODE_SET_METHOD(exports, "setpwent", setpwentMethod);
  NODE_SET_METHOD(exports, "endpwent", endpwentMethod);

  // NODE_SET_METHOD(exports, "getgrent", getgrentMethod);
  NODE_SET_METHOD(exports, "setgrent", setgrentMethod);
  NODE_SET_METHOD(exports, "endgrent", endgrentMethod);

}

NODE_MODULE(getent, init)

/* EOF */
