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

These databases are not yet implemented (fully):

* `group`
* `hosts`
* `services`
* `protocols`
* `networks`

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

