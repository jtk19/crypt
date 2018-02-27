#ifndef __CRYPT_OHLCV_FMT_H__
#define __CRYPT_OHLCV_FMT_H__

#define CRYPT_CONFIG_FILE			"crypt_config.txt"
#define CRYPT_FEEDS_DIR_DEFAULT		"/home/data/crypt_data/"
#define CRYPT_WRITE_DIR_DEFAULT		"/home/data/crypt_ohlcv/"


enum CryptoFeed_T
{
	Feed_BittrexHistory,
	Feed_BitcoinHistory,
    Feed_Unknown
};

#endif
