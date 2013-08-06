/* Node.js Crypt(3) implementation */

#include <node.h>
#include <v8.h>

#include <sys/types.h> // for getpwent, setpwent, endpwent
#include <pwd.h>

#include <errno.h> // for errno
#include <string.h> // for strerror

using namespace v8;

/* Binding for getpwent */
Handle<Value> getpwentMethod(const Arguments& args) {
	HandleScope scope;
	struct passwd *tmp;
	int err;
	errno = 0;
	tmp = getpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		ThrowException(Exception::Error(String::New(strerror(err))));
		return scope.Close(Undefined());
	}

	// Check for end of data
	if(tmp == NULL) {
		return scope.Close(Undefined());
	}

	// Return the data as an object
	Local<Object> obj = Object::New();
	obj->Set(String::NewSymbol("name"),   String::New(tmp->pw_name));
	obj->Set(String::NewSymbol("passwd"), String::New(tmp->pw_passwd));
	obj->Set(String::NewSymbol("uid"),    Number::New(tmp->pw_uid));
	obj->Set(String::NewSymbol("gid"),    Number::New(tmp->pw_gid));
	obj->Set(String::NewSymbol("gecos"),  String::New(tmp->pw_gecos));
	obj->Set(String::NewSymbol("dir"),    String::New(tmp->pw_dir));
	obj->Set(String::NewSymbol("shell"),  String::New(tmp->pw_shell));
	return scope.Close(obj);
}

/* Binding for setpwent */
Handle<Value> setpwentMethod(const Arguments& args) {
	HandleScope scope;
	int err;
	errno = 0;
	setpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		ThrowException(Exception::Error(String::New(strerror(err))));
		return scope.Close(Undefined());
	}

	return scope.Close(Undefined());
}

/* Binding for endpwent */
Handle<Value> endpwentMethod(const Arguments& args) {
	HandleScope scope;
	int err;
	errno = 0;
	endpwent();
	err = errno;

	// Check for errors
	if(err != 0) {
		ThrowException(Exception::Error(String::New(strerror(err))));
		return scope.Close(Undefined());
	}

	return scope.Close(Undefined());
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("getpwent"), FunctionTemplate::New(getpwentMethod)->GetFunction());
	exports->Set(String::NewSymbol("setpwent"), FunctionTemplate::New(setpwentMethod)->GetFunction());
	exports->Set(String::NewSymbol("endpwent"), FunctionTemplate::New(endpwentMethod)->GetFunction());
}

NODE_MODULE(getent, init)

/* EOF */
