// Module for interfacing with the DHTxx sensors (xx = 11-21-22-33-44).

#include "module.h"
#include "lauxlib.h"
#include "platform.h"
#include "cpu_esp8266.h"
#include "dht.h"

#define NUM_DHT GPIO_PIN_NUM

// ****************************************************************************
// DHT functions
int platform_dht_exists( unsigned id )
{
  return ((id < NUM_DHT) && (id > 0));
}

// Lua: status, temp, humi, tempdec, humidec = dht.read( id )
static int dht_lapi_read( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( dht, id );
  lua_pushinteger( L, dht_read_universal(id) );
  double temp = dht_getTemperature();
  double humi = dht_getHumidity();
  int tempdec = (int)((temp - (int)temp) * 1000);
  int humidec = (int)((humi - (int)humi) * 1000);
  lua_pushnumber( L, temp );
  lua_pushnumber( L, humi );
  lua_pushnumber( L, tempdec );
  lua_pushnumber( L, humidec );
  return 5;
}

// Lua: status, temp, humi, tempdec, humidec = dht.read11( id ))
static int dht_lapi_read11( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( dht, id );
  lua_pushinteger( L, dht_read11(id) );
  double temp = dht_getTemperature();
  double humi = dht_getHumidity();
  int tempdec = (int)((temp - (int)temp) * 1000);
  int humidec = (int)((humi - (int)humi) * 1000);
  lua_pushnumber( L, temp );
  lua_pushnumber( L, humi );
  lua_pushnumber( L, tempdec );
  lua_pushnumber( L, humidec );
  return 5;
}

// Lua: status, temp, humi, tempdec, humidec = dht.readxx( id ))
static int dht_lapi_readxx( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( dht, id );
  lua_pushinteger( L, dht_read(id) );
  double temp = dht_getTemperature();
  double humi = dht_getHumidity();
  int tempdec = (int)((temp - (int)temp) * 1000);
  int humidec = (int)((humi - (int)humi) * 1000);
  lua_pushnumber( L, temp );
  lua_pushnumber( L, humi );
  lua_pushnumber( L, tempdec );
  lua_pushnumber( L, humidec );
  return 5;
}

// // Lua: result = dht.humidity()
// static int dht_lapi_humidity( lua_State *L )
// {
//   lua_pushnumber( L, dht_getHumidity() );
//   return 1;
// }

// // Lua: result = dht.humiditydecimal()
// static int dht_lapi_humiditydecimal( lua_State *L )
// {
//   double value = dht_getHumidity();
//   int result = (int)((value - (int)value) * 1000);
//   lua_pushnumber( L, result );
//   return 1;
// }

// // Lua: result = dht.temperature()
// static int dht_lapi_temperature( lua_State *L )
// {
//   lua_pushnumber( L, dht_getTemperature() );
//   return 1;
// }

// // Lua: result = dht.temperaturedecimal()
// static int dht_lapi_temperaturedecimal( lua_State *L )
// {
//   double value = dht_getTemperature();
//   int result = (int)((value - (int)value) * 1000);
//   lua_pushnumber( L, result );
//   return 1;
// }

// Module function map
LROT_BEGIN(dht)
  LROT_FUNCENTRY( read, dht_lapi_read )
  LROT_FUNCENTRY( read11, dht_lapi_read11 )
  LROT_FUNCENTRY( readxx, dht_lapi_readxx )
  LROT_NUMENTRY( OK, DHTLIB_OK )
  LROT_NUMENTRY( ERROR_CHECKSUM, DHTLIB_ERROR_CHECKSUM )
  LROT_NUMENTRY( ERROR_TIMEOUT, DHTLIB_ERROR_TIMEOUT )
LROT_END( dht, NULL, 0 )


NODEMCU_MODULE(DHT, "dht", dht, NULL);
