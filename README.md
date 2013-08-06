node-getent
===========

Get entries from administrative databases for Node.js.

It's Node.js implementation of the getent system call. It's made using same C functions as the original command.

Install
-------

You can install it using NPM: `npm install getent`

Features
--------

Currently supports only these database:

* `passwd`

TODO
----

Generic stuff to do:

* Write unit tests
* Setup travis-ci

Implement these new databases:

* Database passwd - Implement `getpwnam` and `getpwuid` -- Current search does NOT use these!
* Database group - Implement `getgrent` etc
* Database hosts - Implement ` gethostent`
* Database services - Implement `getservent`
* Database protocols - Implement `getprotoent` etc
* Database networks - Implement `getnetent`

Also maybe these (which were not documented for getent command):

* Database shadow - Implement `getspent`, `getspnam`, etc
* Database alias - Implement `getaliasent` etc
* Database rpc - Implement `getrpcent` etc
* Database tty - Implement `getttyent` etc
* Database mnt - Implement `getmntent`

Feel free to submit issues if you would like to see another feature or would need one of these implemented sooner. I'll accept pull requests, too!

Examples
--------

First you must define `getent` like this (did you expect something else?):

```javascript
var getent = require('getent');
```

Fetch all users using a callback:

```javascript
getent.passwd(function(user) {
	console.log( JSON.stringify(user) );
});
```

Fetch all users by returning an array:

```javascript
var users = getent.passwd();
```

Fetch single user:

```javascript
var users = getent.passwd("root");
```

Fetch two users:

```javascript
var users = getent.passwd(["root", "nobody"]);
```

