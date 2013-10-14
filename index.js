/** Node.js getent Library */

var internal =  require('./build/Release/getent');
var databases = {};

/* Implement passwd database search */
databases.passwd = function(keys, fn) {
	var item;
	internal.setpwent();
	try {
		while(item = internal.getpwent()) {
			var key = item && item.name;

			if(key && keys && (keys.indexOf(key) < 0)) {
				continue;
			}

			if(item) {
				fn(item);
			}
		}
	} finally {
		internal.endpwent();
	}
};

/* Implement group database search */
databases.group = function(keys, fn) {
	var item;
	internal.setgrent();
	try {
		while(item = internal.getgrent()) {
			var key = item && item.name;

			if(key && keys && (keys.indexOf(key) < 0)) {
				continue;
			}

			if(item) {
				fn(item);
			}
		}
	} finally {
		internal.endgrent();
	}
};

/** Get entries from administrative database
 * @param {string} database Database name. Currently only supports `passwd`.
 * @param {string|array} keys Key or array of keys to to fetch
 * @param {function} fn Optional function in format function({object} item), which will be called for each item.
 * @returns {undefined|array} Array of items if fn was provided or otherwise undefined.
 */
var getent = module.exports = function getent(database, keys, fn) {
	var items;

	// Enable format getent(db, function(item) { ... })
	if( (fn === undefined) && keys && (typeof keys == 'function') ) {
		fn = keys;
		keys = undefined;
	}

	// Enable format getent(db)
	if(keys !== undefined) {
		keys = (typeof keys === 'object' && keys instanceof Array) ? keys : [keys];
	}

	if(databases[database] === undefined) {
		throw new TypeError("Database not implemented: " + database);
	}

	if(fn === undefined) {
		items = [];
		fn = function(item) { items.push(item); };
	}

	databases[database](keys, fn);

	return items;
}

// Shortcuts
getent.passwd    = getent.bind(undefined, 'passwd');
getent.group     = getent.bind(undefined, 'group');
getent.hosts     = getent.bind(undefined, 'hosts');
getent.services  = getent.bind(undefined, 'services');
getent.protocols = getent.bind(undefined, 'protocols');
getent.networks  = getent.bind(undefined, 'networks');

/* EOF */
