<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the installation.
 * You don't have to use the web site, you can copy this file to "wp-config.php"
 * and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * Database settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** Database settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wp_DB' );

/** Database username */
define( 'DB_USER', 'abelarif' );

/** Database password */
define( 'DB_PASSWORD', 'abelarif' );

/** Database hostname */
define( 'DB_HOST', '0.0.0.0:3306' );

/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         'KBpRJk.Wa9m3O}i%tQq<dLK]b^*?hA,#xRG<AQh[LLDUAYuqWcvJMW[ 4Z0kVLV:' );
define( 'SECURE_AUTH_KEY',  'tDI[sA;ih!4shWi&R(8s^9>kMC1NVtMbm&&X$2>!yZH=[SH_hFofjm,$DGM),N/`' );
define( 'LOGGED_IN_KEY',    '1u %*ab.&)-Q4b%D xx_gA{gnZQJUbLU*`0Gvj<L]&I5a(XDSx#N9/)+>.aaxBcv' );
define( 'NONCE_KEY',        '`%eKp%{LYYx9p?V2wQEZ1)O]gG+sbVftu,#JB!Gh%/:,>67o/H70HWH8q)S;)9`e' );
define( 'AUTH_SALT',        '7MF#sd3Fo:.gJ22s6)qV52V0yi`MSM^o}@i_s/jh/C6[6U8:=;D5`-MpJI>9<c4=' );
define( 'SECURE_AUTH_SALT', 'pI~)H:y[)-LK.uStJ/-z%R]]3Y8U>]o[x5k;8rhD=P8$Bx=~|bVWpSMt^&+QYq3,' );
define( 'LOGGED_IN_SALT',   'L2X.nj}bp)#C}n2XUdYA81AcO,(Jes~p5jE_3<qR5]-!<)d[]@EZWSHw=UunRNu6' );
define( 'NONCE_SALT',       'YgD6apI0dSKA!)j)]kBC~YI{{$@Bje)4^O5EN6]p@EtDYw3k]_Re5<Z$YFDp}uI!' );

/**#@-*/

/**
 * WordPress database table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* Add any custom values between this line and the "stop editing" line. */



/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
