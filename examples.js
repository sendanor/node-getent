
var getent = require('./index.js');

console.log("Fetch all users using callback:");
getent.passwd(function(user) {
	console.log( JSON.stringify(user) );
});
console.log("-EOL-");

console.log("Fetch all users by returning an array:");
var users = getent.passwd();
console.log( JSON.stringify(users) );
console.log("-EOL-");

console.log("Fetch only user root:");
var users = getent.passwd("root");
console.log( JSON.stringify(users) );
console.log("-EOL-");

console.log("Fetch root and nobody:");
var users = getent.passwd(["root", "nobody"]);
console.log( JSON.stringify(users) );
console.log("-EOL-");
