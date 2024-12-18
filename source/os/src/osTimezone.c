/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define ALLOW_FORBID_FUNC
#define _DEFAULT_SOURCE
#include "os.h"

#ifdef WINDOWS
#if (_WIN64)
#include <iphlpapi.h>
#include <mswsock.h>
#include <psapi.h>
#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Mswsock.lib ")
#endif
#include <objbase.h>
#pragma warning(push)
#pragma warning(disable : 4091)
#include <DbgHelp.h>
#pragma warning(pop)

#define W_TZ_NUM 139
char *win_tz[W_TZ_NUM][2] = {{"China Standard Time", "Asia/Shanghai"},
                        {"AUS Central Standard Time", "Australia/Darwin"},
                        {"AUS Eastern Standard Time", "Australia/Sydney"},
                        {"Afghanistan Standard Time", "Asia/Kabul"},
                        {"Alaskan Standard Time", "America/Anchorage"},
                        {"Aleutian Standard Time", "America/Adak"},
                        {"Altai Standard Time", "Asia/Barnaul"},
                        {"Arab Standard Time", "Asia/Riyadh"},
                        {"Arabian Standard Time", "Asia/Dubai"},
                        {"Arabic Standard Time", "Asia/Baghdad"},
                        {"Argentina Standard Time", "America/Buenos_Aires"},
                        {"Astrakhan Standard Time", "Europe/Astrakhan"},
                        {"Atlantic Standard Time", "America/Halifax"},
                        {"Aus Central W. Standard Time", "Australia/Eucla"},
                        {"Azerbaijan Standard Time", "Asia/Baku"},
                        {"Azores Standard Time", "Atlantic/Azores"},
                        {"Bahia Standard Time", "America/Bahia"},
                        {"Bangladesh Standard Time", "Asia/Dhaka"},
                        {"Belarus Standard Time", "Europe/Minsk"},
                        {"Bougainville Standard Time", "Pacific/Bougainville"},
                        {"Canada Central Standard Time", "America/Regina"},
                        {"Cape Verde Standard Time", "Atlantic/Cape_Verde"},
                        {"Caucasus Standard Time", "Asia/Yerevan"},
                        {"Cen. Australia Standard Time", "Australia/Adelaide"},
                        {"Central America Standard Time", "America/Guatemala"},
                        {"Central Asia Standard Time", "Asia/Almaty"},
                        {"Central Brazilian Standard Time", "America/Cuiaba"},
                        {"Central Europe Standard Time", "Europe/Budapest"},
                        {"Central European Standard Time", "Europe/Warsaw"},
                        {"Central Pacific Standard Time", "Pacific/Guadalcanal"},
                        {"Central Standard Time", "America/Chicago"},
                        {"Central Standard Time (Mexico)", "America/Mexico_City"},
                        {"Chatham Islands Standard Time", "Pacific/Chatham"},
                        {"Cuba Standard Time", "America/Havana"},
                        {"Dateline Standard Time", "Etc/GMT+12"},
                        {"E. Africa Standard Time", "Africa/Nairobi"},
                        {"E. Australia Standard Time", "Australia/Brisbane"},
                        {"E. Europe Standard Time", "Europe/Chisinau"},
                        {"E. South America Standard Time", "America/Sao_Paulo"},
                        {"Easter Island Standard Time", "Pacific/Easter"},
                        {"Eastern Standard Time", "America/New_York"},
                        {"Eastern Standard Time (Mexico)", "America/Cancun"},
                        {"Egypt Standard Time", "Africa/Cairo"},
                        {"Ekaterinburg Standard Time", "Asia/Yekaterinburg"},
                        {"FLE Standard Time", "Europe/Kiev"},
                        {"Fiji Standard Time", "Pacific/Fiji"},
                        {"GMT Standard Time", "Europe/London"},
                        {"GTB Standard Time", "Europe/Bucharest"},
                        {"Georgian Standard Time", "Asia/Tbilisi"},
                        {"Greenland Standard Time", "America/Godthab"},
                        {"Greenwich Standard Time", "Atlantic/Reykjavik"},
                        {"Haiti Standard Time", "America/Port-au-Prince"},
                        {"Hawaiian Standard Time", "Pacific/Honolulu"},
                        {"India Standard Time", "Asia/Calcutta"},
                        {"Iran Standard Time", "Asia/Tehran"},
                        {"Israel Standard Time", "Asia/Jerusalem"},
                        {"Jordan Standard Time", "Asia/Amman"},
                        {"Kaliningrad Standard Time", "Europe/Kaliningrad"},
                        {"Korea Standard Time", "Asia/Seoul"},
                        {"Libya Standard Time", "Africa/Tripoli"},
                        {"Line Islands Standard Time", "Pacific/Kiritimati"},
                        {"Lord Howe Standard Time", "Australia/Lord_Howe"},
                        {"Magadan Standard Time", "Asia/Magadan"},
                        {"Magallanes Standard Time", "America/Punta_Arenas"},
                        {"Marquesas Standard Time", "Pacific/Marquesas"},
                        {"Mauritius Standard Time", "Indian/Mauritius"},
                        {"Middle East Standard Time", "Asia/Beirut"},
                        {"Montevideo Standard Time", "America/Montevideo"},
                        {"Morocco Standard Time", "Africa/Casablanca"},
                        {"Mountain Standard Time", "America/Denver"},
                        {"Mountain Standard Time (Mexico)", "America/Chihuahua"},
                        {"Myanmar Standard Time", "Asia/Rangoon"},
                        {"N. Central Asia Standard Time", "Asia/Novosibirsk"},
                        {"Namibia Standard Time", "Africa/Windhoek"},
                        {"Nepal Standard Time", "Asia/Katmandu"},
                        {"New Zealand Standard Time", "Pacific/Auckland"},
                        {"Newfoundland Standard Time", "America/St_Johns"},
                        {"Norfolk Standard Time", "Pacific/Norfolk"},
                        {"North Asia East Standard Time", "Asia/Irkutsk"},
                        {"North Asia Standard Time", "Asia/Krasnoyarsk"},
                        {"North Korea Standard Time", "Asia/Pyongyang"},
                        {"Omsk Standard Time", "Asia/Omsk"},
                        {"Pacific SA Standard Time", "America/Santiago"},
                        {"Pacific Standard Time", "America/Los_Angeles"},
                        {"Pacific Standard Time (Mexico)", "America/Tijuana"},
                        {"Pakistan Standard Time", "Asia/Karachi"},
                        {"Paraguay Standard Time", "America/Asuncion"},
                        {"Qyzylorda Standard Time", "Asia/Qyzylorda"},
                        {"Romance Standard Time", "Europe/Paris"},
                        {"Russia Time Zone 10", "Asia/Srednekolymsk"},
                        {"Russia Time Zone 11", "Asia/Kamchatka"},
                        {"Russia Time Zone 3", "Europe/Samara"},
                        {"Russian Standard Time", "Europe/Moscow"},
                        {"SA Eastern Standard Time", "America/Cayenne"},
                        {"SA Pacific Standard Time", "America/Bogota"},
                        {"SA Western Standard Time", "America/La_Paz"},
                        {"SE Asia Standard Time", "Asia/Bangkok"},
                        {"Saint Pierre Standard Time", "America/Miquelon"},
                        {"Sakhalin Standard Time", "Asia/Sakhalin"},
                        {"Samoa Standard Time", "Pacific/Apia"},
                        {"Sao Tome Standard Time", "Africa/Sao_Tome"},
                        {"Saratov Standard Time", "Europe/Saratov"},
                        {"Singapore Standard Time", "Asia/Singapore"},
                        {"South Africa Standard Time", "Africa/Johannesburg"},
                        {"South Sudan Standard Time", "Africa/Juba"},
                        {"Sri Lanka Standard Time", "Asia/Colombo"},
                        {"Sudan Standard Time", "Africa/Khartoum"},
                        {"Syria Standard Time", "Asia/Damascus"},
                        {"Taipei Standard Time", "Asia/Taipei"},
                        {"Tasmania Standard Time", "Australia/Hobart"},
                        {"Tocantins Standard Time", "America/Araguaina"},
                        {"Tokyo Standard Time", "Asia/Tokyo"},
                        {"Tomsk Standard Time", "Asia/Tomsk"},
                        {"Tonga Standard Time", "Pacific/Tongatapu"},
                        {"Transbaikal Standard Time", "Asia/Chita"},
                        {"Turkey Standard Time", "Europe/Istanbul"},
                        {"Turks And Caicos Standard Time", "America/Grand_Turk"},
                        {"US Eastern Standard Time", "America/Indianapolis"},
                        {"US Mountain Standard Time", "America/Phoenix"},
                        {"UTC", "Etc/UTC"},
                        {"UTC+12", "Etc/GMT-12"},
                        {"UTC+13", "Etc/GMT-13"},
                        {"UTC-02", "Etc/GMT+2"},
                        {"UTC-08", "Etc/GMT+8"},
                        {"UTC-09", "Etc/GMT+9"},
                        {"UTC-11", "Etc/GMT+11"},
                        {"Ulaanbaatar Standard Time", "Asia/Ulaanbaatar"},
                        {"Venezuela Standard Time", "America/Caracas"},
                        {"Vladivostok Standard Time", "Asia/Vladivostok"},
                        {"Volgograd Standard Time", "Europe/Volgograd"},
                        {"W. Australia Standard Time", "Australia/Perth"},
                        {"W. Central Africa Standard Time", "Africa/Lagos"},
                        {"W. Europe Standard Time", "Europe/Berlin"},
                        {"W. Mongolia Standard Time", "Asia/Hovd"},
                        {"West Asia Standard Time", "Asia/Tashkent"},
                        {"West Bank Standard Time", "Asia/Hebron"},
                        {"West Pacific Standard Time", "Pacific/Port_Moresby"},
                        {"Yakutsk Standard Time", "Asia/Yakutsk"},
                        {"Yukon Standard Time", "America/Whitehorse"}};
#define W_TZ_CITY_NUM 554
char *tz_win[W_TZ_CITY_NUM][2] = {{"Asia/Shanghai", "China Standard Time"},
                        {"Africa/Abidjan", "Greenwich Standard Time"},
                        {"Africa/Accra", "Greenwich Standard Time"},
                        {"Africa/Addis_Ababa", "E. Africa Standard Time"},
                        {"Africa/Algiers", "W. Central Africa Standard Time"},
                        {"Africa/Asmera", "E. Africa Standard Time"},
                        {"Africa/Bamako", "Greenwich Standard Time"},
                        {"Africa/Bangui", "W. Central Africa Standard Time"},
                        {"Africa/Banjul", "Greenwich Standard Time"},
                        {"Africa/Bissau", "Greenwich Standard Time"},
                        {"Africa/Blantyre", "South Africa Standard Time"},
                        {"Africa/Brazzaville", "W. Central Africa Standard Time"},
                        {"Africa/Bujumbura", "South Africa Standard Time"},
                        {"Africa/Cairo", "Egypt Standard Time"},
                        {"Africa/Casablanca", "Morocco Standard Time"},
                        {"Africa/Ceuta", "Romance Standard Time"},
                        {"Africa/Conakry", "Greenwich Standard Time"},
                        {"Africa/Dakar", "Greenwich Standard Time"},
                        {"Africa/Dar_es_Salaam", "E. Africa Standard Time"},
                        {"Africa/Djibouti", "E. Africa Standard Time"},
                        {"Africa/Douala", "W. Central Africa Standard Time"},
                        {"Africa/El_Aaiun", "Morocco Standard Time"},
                        {"Africa/Freetown", "Greenwich Standard Time"},
                        {"Africa/Gaborone", "South Africa Standard Time"},
                        {"Africa/Harare", "South Africa Standard Time"},
                        {"Africa/Johannesburg", "South Africa Standard Time"},
                        {"Africa/Juba", "South Sudan Standard Time"},
                        {"Africa/Kampala", "E. Africa Standard Time"},
                        {"Africa/Khartoum", "Sudan Standard Time"},
                        {"Africa/Kigali", "South Africa Standard Time"},
                        {"Africa/Kinshasa", "W. Central Africa Standard Time"},
                        {"Africa/Lagos", "W. Central Africa Standard Time"},
                        {"Africa/Libreville", "W. Central Africa Standard Time"},
                        {"Africa/Lome", "Greenwich Standard Time"},
                        {"Africa/Luanda", "W. Central Africa Standard Time"},
                        {"Africa/Lubumbashi", "South Africa Standard Time"},
                        {"Africa/Lusaka", "South Africa Standard Time"},
                        {"Africa/Malabo", "W. Central Africa Standard Time"},
                        {"Africa/Maputo", "South Africa Standard Time"},
                        {"Africa/Maseru", "South Africa Standard Time"},
                        {"Africa/Mbabane", "South Africa Standard Time"},
                        {"Africa/Mogadishu", "E. Africa Standard Time"},
                        {"Africa/Monrovia", "Greenwich Standard Time"},
                        {"Africa/Nairobi", "E. Africa Standard Time"},
                        {"Africa/Ndjamena", "W. Central Africa Standard Time"},
                        {"Africa/Niamey", "W. Central Africa Standard Time"},
                        {"Africa/Nouakchott", "Greenwich Standard Time"},
                        {"Africa/Ouagadougou", "Greenwich Standard Time"},
                        {"Africa/Porto-Novo", "W. Central Africa Standard Time"},
                        {"Africa/Sao_Tome", "Sao Tome Standard Time"},
                        {"Africa/Timbuktu", "Greenwich Standard Time"},
                        {"Africa/Tripoli", "Libya Standard Time"},
                        {"Africa/Tunis", "W. Central Africa Standard Time"},
                        {"Africa/Windhoek", "Namibia Standard Time"},
                        {"America/Adak", "Aleutian Standard Time"},
                        {"America/Anchorage", "Alaskan Standard Time"},
                        {"America/Anguilla", "SA Western Standard Time"},
                        {"America/Antigua", "SA Western Standard Time"},
                        {"America/Araguaina", "Tocantins Standard Time"},
                        {"America/Argentina/La_Rioja", "Argentina Standard Time"},
                        {"America/Argentina/Rio_Gallegos", "Argentina Standard Time"},
                        {"America/Argentina/Salta", "Argentina Standard Time"},
                        {"America/Argentina/San_Juan", "Argentina Standard Time"},
                        {"America/Argentina/San_Luis", "Argentina Standard Time"},
                        {"America/Argentina/Tucuman", "Argentina Standard Time"},
                        {"America/Argentina/Ushuaia", "Argentina Standard Time"},
                        {"America/Aruba", "SA Western Standard Time"},
                        {"America/Asuncion", "Paraguay Standard Time"},
                        {"America/Atka", "Aleutian Standard Time"},
                        {"America/Bahia", "Bahia Standard Time"},
                        {"America/Bahia_Banderas", "Central Standard Time (Mexico)"},
                        {"America/Barbados", "SA Western Standard Time"},
                        {"America/Belem", "SA Eastern Standard Time"},
                        {"America/Belize", "Central America Standard Time"},
                        {"America/Blanc-Sablon", "SA Western Standard Time"},
                        {"America/Boa_Vista", "SA Western Standard Time"},
                        {"America/Bogota", "SA Pacific Standard Time"},
                        {"America/Boise", "Mountain Standard Time"},
                        {"America/Buenos_Aires", "Argentina Standard Time"},
                        {"America/Cambridge_Bay", "Mountain Standard Time"},
                        {"America/Campo_Grande", "Central Brazilian Standard Time"},
                        {"America/Cancun", "Eastern Standard Time (Mexico)"},
                        {"America/Caracas", "Venezuela Standard Time"},
                        {"America/Catamarca", "Argentina Standard Time"},
                        {"America/Cayenne", "SA Eastern Standard Time"},
                        {"America/Cayman", "SA Pacific Standard Time"},
                        {"America/Chicago", "Central Standard Time"},
                        {"America/Chihuahua", "Mountain Standard Time (Mexico)"},
                        {"America/Coral_Harbour", "SA Pacific Standard Time"},
                        {"America/Cordoba", "Argentina Standard Time"},
                        {"America/Costa_Rica", "Central America Standard Time"},
                        {"America/Creston", "US Mountain Standard Time"},
                        {"America/Cuiaba", "Central Brazilian Standard Time"},
                        {"America/Curacao", "SA Western Standard Time"},
                        {"America/Danmarkshavn", "Greenwich Standard Time"},
                        {"America/Dawson", "Yukon Standard Time"},
                        {"America/Dawson_Creek", "US Mountain Standard Time"},
                        {"America/Denver", "Mountain Standard Time"},
                        {"America/Detroit", "Eastern Standard Time"},
                        {"America/Dominica", "SA Western Standard Time"},
                        {"America/Edmonton", "Mountain Standard Time"},
                        {"America/Eirunepe", "SA Pacific Standard Time"},
                        {"America/El_Salvador", "Central America Standard Time"},
                        {"America/Ensenada", "Pacific Standard Time (Mexico)"},
                        {"America/Fort_Nelson", "US Mountain Standard Time"},
                        {"America/Fortaleza", "SA Eastern Standard Time"},
                        {"America/Glace_Bay", "Atlantic Standard Time"},
                        {"America/Godthab", "Greenland Standard Time"},
                        {"America/Goose_Bay", "Atlantic Standard Time"},
                        {"America/Grand_Turk", "Turks And Caicos Standard Time"},
                        {"America/Grenada", "SA Western Standard Time"},
                        {"America/Guadeloupe", "SA Western Standard Time"},
                        {"America/Guatemala", "Central America Standard Time"},
                        {"America/Guayaquil", "SA Pacific Standard Time"},
                        {"America/Guyana", "SA Western Standard Time"},
                        {"America/Halifax", "Atlantic Standard Time"},
                        {"America/Havana", "Cuba Standard Time"},
                        {"America/Hermosillo", "US Mountain Standard Time"},
                        {"America/Indiana/Knox", "Central Standard Time"},
                        {"America/Indiana/Marengo", "US Eastern Standard Time"},
                        {"America/Indiana/Petersburg", "Eastern Standard Time"},
                        {"America/Indiana/Tell_City", "Central Standard Time"},
                        {"America/Indiana/Vevay", "US Eastern Standard Time"},
                        {"America/Indiana/Vincennes", "Eastern Standard Time"},
                        {"America/Indiana/Winamac", "Eastern Standard Time"},
                        {"America/Indianapolis", "US Eastern Standard Time"},
                        {"America/Inuvik", "Mountain Standard Time"},
                        {"America/Iqaluit", "Eastern Standard Time"},
                        {"America/Jamaica", "SA Pacific Standard Time"},
                        {"America/Jujuy", "Argentina Standard Time"},
                        {"America/Juneau", "Alaskan Standard Time"},
                        {"America/Kentucky/Monticello", "Eastern Standard Time"},
                        {"America/Knox_IN", "Central Standard Time"},
                        {"America/Kralendijk", "SA Western Standard Time"},
                        {"America/La_Paz", "SA Western Standard Time"},
                        {"America/Lima", "SA Pacific Standard Time"},
                        {"America/Los_Angeles", "Pacific Standard Time"},
                        {"America/Louisville", "Eastern Standard Time"},
                        {"America/Lower_Princes", "SA Western Standard Time"},
                        {"America/Maceio", "SA Eastern Standard Time"},
                        {"America/Managua", "Central America Standard Time"},
                        {"America/Manaus", "SA Western Standard Time"},
                        {"America/Marigot", "SA Western Standard Time"},
                        {"America/Martinique", "SA Western Standard Time"},
                        {"America/Matamoros", "Central Standard Time"},
                        {"America/Mazatlan", "Mountain Standard Time (Mexico)"},
                        {"America/Mendoza", "Argentina Standard Time"},
                        {"America/Menominee", "Central Standard Time"},
                        {"America/Merida", "Central Standard Time (Mexico)"},
                        {"America/Metlakatla", "Alaskan Standard Time"},
                        {"America/Mexico_City", "Central Standard Time (Mexico)"},
                        {"America/Miquelon", "Saint Pierre Standard Time"},
                        {"America/Moncton", "Atlantic Standard Time"},
                        {"America/Monterrey", "Central Standard Time (Mexico)"},
                        {"America/Montevideo", "Montevideo Standard Time"},
                        {"America/Montreal", "Eastern Standard Time"},
                        {"America/Montserrat", "SA Western Standard Time"},
                        {"America/Nassau", "Eastern Standard Time"},
                        {"America/New_York", "Eastern Standard Time"},
                        {"America/Nipigon", "Eastern Standard Time"},
                        {"America/Nome", "Alaskan Standard Time"},
                        {"America/Noronha", "UTC-02"},
                        {"America/North_Dakota/Beulah", "Central Standard Time"},
                        {"America/North_Dakota/Center", "Central Standard Time"},
                        {"America/North_Dakota/New_Salem", "Central Standard Time"},
                        {"America/Ojinaga", "Mountain Standard Time"},
                        {"America/Panama", "SA Pacific Standard Time"},
                        {"America/Pangnirtung", "Eastern Standard Time"},
                        {"America/Paramaribo", "SA Eastern Standard Time"},
                        {"America/Phoenix", "US Mountain Standard Time"},
                        {"America/Port-au-Prince", "Haiti Standard Time"},
                        {"America/Port_of_Spain", "SA Western Standard Time"},
                        {"America/Porto_Acre", "SA Pacific Standard Time"},
                        {"America/Porto_Velho", "SA Western Standard Time"},
                        {"America/Puerto_Rico", "SA Western Standard Time"},
                        {"America/Punta_Arenas", "Magallanes Standard Time"},
                        {"America/Rainy_River", "Central Standard Time"},
                        {"America/Rankin_Inlet", "Central Standard Time"},
                        {"America/Recife", "SA Eastern Standard Time"},
                        {"America/Regina", "Canada Central Standard Time"},
                        {"America/Resolute", "Central Standard Time"},
                        {"America/Rio_Branco", "SA Pacific Standard Time"},
                        {"America/Santa_Isabel", "Pacific Standard Time (Mexico)"},
                        {"America/Santarem", "SA Eastern Standard Time"},
                        {"America/Santiago", "Pacific SA Standard Time"},
                        {"America/Santo_Domingo", "SA Western Standard Time"},
                        {"America/Sao_Paulo", "E. South America Standard Time"},
                        {"America/Scoresbysund", "Azores Standard Time"},
                        {"America/Shiprock", "Mountain Standard Time"},
                        {"America/Sitka", "Alaskan Standard Time"},
                        {"America/St_Barthelemy", "SA Western Standard Time"},
                        {"America/St_Johns", "Newfoundland Standard Time"},
                        {"America/St_Kitts", "SA Western Standard Time"},
                        {"America/St_Lucia", "SA Western Standard Time"},
                        {"America/St_Thomas", "SA Western Standard Time"},
                        {"America/St_Vincent", "SA Western Standard Time"},
                        {"America/Swift_Current", "Canada Central Standard Time"},
                        {"America/Tegucigalpa", "Central America Standard Time"},
                        {"America/Thule", "Atlantic Standard Time"},
                        {"America/Thunder_Bay", "Eastern Standard Time"},
                        {"America/Tijuana", "Pacific Standard Time (Mexico)"},
                        {"America/Toronto", "Eastern Standard Time"},
                        {"America/Tortola", "SA Western Standard Time"},
                        {"America/Vancouver", "Pacific Standard Time"},
                        {"America/Virgin", "SA Western Standard Time"},
                        {"America/Whitehorse", "Yukon Standard Time"},
                        {"America/Winnipeg", "Central Standard Time"},
                        {"America/Yakutat", "Alaskan Standard Time"},
                        {"America/Yellowknife", "Mountain Standard Time"},
                        {"Antarctica/Casey", "Central Pacific Standard Time"},
                        {"Antarctica/Davis", "SE Asia Standard Time"},
                        {"Antarctica/DumontDUrville", "West Pacific Standard Time"},
                        {"Antarctica/Macquarie", "Tasmania Standard Time"},
                        {"Antarctica/Mawson", "West Asia Standard Time"},
                        {"Antarctica/McMurdo", "New Zealand Standard Time"},
                        {"Antarctica/Palmer", "SA Eastern Standard Time"},
                        {"Antarctica/Rothera", "SA Eastern Standard Time"},
                        {"Antarctica/South_Pole", "New Zealand Standard Time"},
                        {"Antarctica/Syowa", "E. Africa Standard Time"},
                        {"Antarctica/Vostok", "Central Asia Standard Time"},
                        {"Arctic/Longyearbyen", "W. Europe Standard Time"},
                        {"Asia/Aden", "Arab Standard Time"},
                        {"Asia/Almaty", "Central Asia Standard Time"},
                        {"Asia/Amman", "Jordan Standard Time"},
                        {"Asia/Anadyr", "Russia Time Zone 11"},
                        {"Asia/Aqtau", "West Asia Standard Time"},
                        {"Asia/Aqtobe", "West Asia Standard Time"},
                        {"Asia/Ashgabat", "West Asia Standard Time"},
                        {"Asia/Ashkhabad", "West Asia Standard Time"},
                        {"Asia/Atyrau", "West Asia Standard Time"},
                        {"Asia/Baghdad", "Arabic Standard Time"},
                        {"Asia/Bahrain", "Arab Standard Time"},
                        {"Asia/Baku", "Azerbaijan Standard Time"},
                        {"Asia/Bangkok", "SE Asia Standard Time"},
                        {"Asia/Barnaul", "Altai Standard Time"},
                        {"Asia/Beirut", "Middle East Standard Time"},
                        {"Asia/Bishkek", "Central Asia Standard Time"},
                        {"Asia/Brunei", "Singapore Standard Time"},
                        {"Asia/Calcutta", "India Standard Time"},
                        {"Asia/Chita", "Transbaikal Standard Time"},
                        {"Asia/Choibalsan", "Ulaanbaatar Standard Time"},
                        {"Asia/Chongqing", "China Standard Time"},
                        {"Asia/Chungking", "China Standard Time"},
                        {"Asia/Colombo", "Sri Lanka Standard Time"},
                        {"Asia/Dacca", "Bangladesh Standard Time"},
                        {"Asia/Damascus", "Syria Standard Time"},
                        {"Asia/Dhaka", "Bangladesh Standard Time"},
                        {"Asia/Dili", "Tokyo Standard Time"},
                        {"Asia/Dubai", "Arabian Standard Time"},
                        {"Asia/Dushanbe", "West Asia Standard Time"},
                        {"Asia/Famagusta", "GTB Standard Time"},
                        {"Asia/Gaza", "West Bank Standard Time"},
                        {"Asia/Harbin", "China Standard Time"},
                        {"Asia/Hebron", "West Bank Standard Time"},
                        {"Asia/Hong_Kong", "China Standard Time"},
                        {"Asia/Hovd", "W. Mongolia Standard Time"},
                        {"Asia/Irkutsk", "North Asia East Standard Time"},
                        {"Asia/Jakarta", "SE Asia Standard Time"},
                        {"Asia/Jayapura", "Tokyo Standard Time"},
                        {"Asia/Jerusalem", "Israel Standard Time"},
                        {"Asia/Kabul", "Afghanistan Standard Time"},
                        {"Asia/Kamchatka", "Russia Time Zone 11"},
                        {"Asia/Karachi", "Pakistan Standard Time"},
                        {"Asia/Kashgar", "Central Asia Standard Time"},
                        {"Asia/Katmandu", "Nepal Standard Time"},
                        {"Asia/Khandyga", "Yakutsk Standard Time"},
                        {"Asia/Krasnoyarsk", "North Asia Standard Time"},
                        {"Asia/Kuala_Lumpur", "Singapore Standard Time"},
                        {"Asia/Kuching", "Singapore Standard Time"},
                        {"Asia/Kuwait", "Arab Standard Time"},
                        {"Asia/Macao", "China Standard Time"},
                        {"Asia/Macau", "China Standard Time"},
                        {"Asia/Magadan", "Magadan Standard Time"},
                        {"Asia/Makassar", "Singapore Standard Time"},
                        {"Asia/Manila", "Singapore Standard Time"},
                        {"Asia/Muscat", "Arabian Standard Time"},
                        {"Asia/Nicosia", "GTB Standard Time"},
                        {"Asia/Novokuznetsk", "North Asia Standard Time"},
                        {"Asia/Novosibirsk", "N. Central Asia Standard Time"},
                        {"Asia/Omsk", "Omsk Standard Time"},
                        {"Asia/Oral", "West Asia Standard Time"},
                        {"Asia/Phnom_Penh", "SE Asia Standard Time"},
                        {"Asia/Pontianak", "SE Asia Standard Time"},
                        {"Asia/Pyongyang", "North Korea Standard Time"},
                        {"Asia/Qatar", "Arab Standard Time"},
                        {"Asia/Qostanay", "Central Asia Standard Time"},
                        {"Asia/Qyzylorda", "Qyzylorda Standard Time"},
                        {"Asia/Rangoon", "Myanmar Standard Time"},
                        {"Asia/Riyadh", "Arab Standard Time"},
                        {"Asia/Saigon", "SE Asia Standard Time"},
                        {"Asia/Sakhalin", "Sakhalin Standard Time"},
                        {"Asia/Samarkand", "West Asia Standard Time"},
                        {"Asia/Seoul", "Korea Standard Time"},
                        {"Asia/Singapore", "Singapore Standard Time"},
                        {"Asia/Srednekolymsk", "Russia Time Zone 10"},
                        {"Asia/Taipei", "Taipei Standard Time"},
                        {"Asia/Tashkent", "West Asia Standard Time"},
                        {"Asia/Tbilisi", "Georgian Standard Time"},
                        {"Asia/Tehran", "Iran Standard Time"},
                        {"Asia/Tel_Aviv", "Israel Standard Time"},
                        {"Asia/Thimbu", "Bangladesh Standard Time"},
                        {"Asia/Thimphu", "Bangladesh Standard Time"},
                        {"Asia/Tokyo", "Tokyo Standard Time"},
                        {"Asia/Tomsk", "Tomsk Standard Time"},
                        {"Asia/Ujung_Pandang", "Singapore Standard Time"},
                        {"Asia/Ulaanbaatar", "Ulaanbaatar Standard Time"},
                        {"Asia/Ulan_Bator", "Ulaanbaatar Standard Time"},
                        {"Asia/Urumqi", "Central Asia Standard Time"},
                        {"Asia/Ust-Nera", "Vladivostok Standard Time"},
                        {"Asia/Vientiane", "SE Asia Standard Time"},
                        {"Asia/Vladivostok", "Vladivostok Standard Time"},
                        {"Asia/Yakutsk", "Yakutsk Standard Time"},
                        {"Asia/Yekaterinburg", "Ekaterinburg Standard Time"},
                        {"Asia/Yerevan", "Caucasus Standard Time"},
                        {"Atlantic/Azores", "Azores Standard Time"},
                        {"Atlantic/Bermuda", "Atlantic Standard Time"},
                        {"Atlantic/Canary", "GMT Standard Time"},
                        {"Atlantic/Cape_Verde", "Cape Verde Standard Time"},
                        {"Atlantic/Faeroe", "GMT Standard Time"},
                        {"Atlantic/Jan_Mayen", "W. Europe Standard Time"},
                        {"Atlantic/Madeira", "GMT Standard Time"},
                        {"Atlantic/Reykjavik", "Greenwich Standard Time"},
                        {"Atlantic/South_Georgia", "UTC-02"},
                        {"Atlantic/St_Helena", "Greenwich Standard Time"},
                        {"Atlantic/Stanley", "SA Eastern Standard Time"},
                        {"Australia/ACT", "AUS Eastern Standard Time"},
                        {"Australia/Adelaide", "Cen. Australia Standard Time"},
                        {"Australia/Brisbane", "E. Australia Standard Time"},
                        {"Australia/Broken_Hill", "Cen. Australia Standard Time"},
                        {"Australia/Canberra", "AUS Eastern Standard Time"},
                        {"Australia/Currie", "Tasmania Standard Time"},
                        {"Australia/Darwin", "AUS Central Standard Time"},
                        {"Australia/Eucla", "Aus Central W. Standard Time"},
                        {"Australia/Hobart", "Tasmania Standard Time"},
                        {"Australia/LHI", "Lord Howe Standard Time"},
                        {"Australia/Lindeman", "E. Australia Standard Time"},
                        {"Australia/Lord_Howe", "Lord Howe Standard Time"},
                        {"Australia/Melbourne", "AUS Eastern Standard Time"},
                        {"Australia/NSW", "AUS Eastern Standard Time"},
                        {"Australia/North", "AUS Central Standard Time"},
                        {"Australia/Perth", "W. Australia Standard Time"},
                        {"Australia/Queensland", "E. Australia Standard Time"},
                        {"Australia/South", "Cen. Australia Standard Time"},
                        {"Australia/Sydney", "AUS Eastern Standard Time"},
                        {"Australia/Tasmania", "Tasmania Standard Time"},
                        {"Australia/Victoria", "AUS Eastern Standard Time"},
                        {"Australia/West", "W. Australia Standard Time"},
                        {"Australia/Yancowinna", "Cen. Australia Standard Time"},
                        {"Brazil/Acre", "SA Pacific Standard Time"},
                        {"Brazil/DeNoronha", "UTC-02"},
                        {"Brazil/East", "E. South America Standard Time"},
                        {"Brazil/West", "SA Western Standard Time"},
                        {"CST6CDT", "Central Standard Time"},
                        {"Canada/Atlantic", "Atlantic Standard Time"},
                        {"Canada/Central", "Central Standard Time"},
                        {"Canada/Eastern", "Eastern Standard Time"},
                        {"Canada/Mountain", "Mountain Standard Time"},
                        {"Canada/Newfoundland", "Newfoundland Standard Time"},
                        {"Canada/Pacific", "Pacific Standard Time"},
                        {"Canada/Saskatchewan", "Canada Central Standard Time"},
                        {"Canada/Yukon", "Yukon Standard Time"},
                        {"Chile/Continental", "Pacific SA Standard Time"},
                        {"Chile/EasterIsland", "Easter Island Standard Time"},
                        {"Cuba", "Cuba Standard Time"},
                        {"EST5EDT", "Eastern Standard Time"},
                        {"Egypt", "Egypt Standard Time"},
                        {"Eire", "GMT Standard Time"},
                        {"Etc/GMT", "UTC"},
                        {"Etc/GMT+1", "Cape Verde Standard Time"},
                        {"Etc/GMT+10", "Hawaiian Standard Time"},
                        {"Etc/GMT+11", "UTC-11"},
                        {"Etc/GMT+12", "Dateline Standard Time"},
                        {"Etc/GMT+2", "UTC-02"},
                        {"Etc/GMT+3", "SA Eastern Standard Time"},
                        {"Etc/GMT+4", "SA Western Standard Time"},
                        {"Etc/GMT+5", "SA Pacific Standard Time"},
                        {"Etc/GMT+6", "Central America Standard Time"},
                        {"Etc/GMT+7", "US Mountain Standard Time"},
                        {"Etc/GMT+8", "UTC-08"},
                        {"Etc/GMT+9", "UTC-09"},
                        {"Etc/GMT-1", "W. Central Africa Standard Time"},
                        {"Etc/GMT-10", "West Pacific Standard Time"},
                        {"Etc/GMT-11", "Central Pacific Standard Time"},
                        {"Etc/GMT-12", "UTC+12"},
                        {"Etc/GMT-13", "UTC+13"},
                        {"Etc/GMT-14", "Line Islands Standard Time"},
                        {"Etc/GMT-2", "South Africa Standard Time"},
                        {"Etc/GMT-3", "E. Africa Standard Time"},
                        {"Etc/GMT-4", "Arabian Standard Time"},
                        {"Etc/GMT-5", "West Asia Standard Time"},
                        {"Etc/GMT-6", "Central Asia Standard Time"},
                        {"Etc/GMT-7", "SE Asia Standard Time"},
                        {"Etc/GMT-8", "Singapore Standard Time"},
                        {"Etc/GMT-9", "Tokyo Standard Time"},
                        {"Etc/UCT", "UTC"},
                        {"Etc/UTC", "UTC"},
                        {"Europe/Amsterdam", "W. Europe Standard Time"},
                        {"Europe/Andorra", "W. Europe Standard Time"},
                        {"Europe/Astrakhan", "Astrakhan Standard Time"},
                        {"Europe/Athens", "GTB Standard Time"},
                        {"Europe/Belfast", "GMT Standard Time"},
                        {"Europe/Belgrade", "Central Europe Standard Time"},
                        {"Europe/Berlin", "W. Europe Standard Time"},
                        {"Europe/Bratislava", "Central Europe Standard Time"},
                        {"Europe/Brussels", "Romance Standard Time"},
                        {"Europe/Bucharest", "GTB Standard Time"},
                        {"Europe/Budapest", "Central Europe Standard Time"},
                        {"Europe/Busingen", "W. Europe Standard Time"},
                        {"Europe/Chisinau", "E. Europe Standard Time"},
                        {"Europe/Copenhagen", "Romance Standard Time"},
                        {"Europe/Dublin", "GMT Standard Time"},
                        {"Europe/Gibraltar", "W. Europe Standard Time"},
                        {"Europe/Guernsey", "GMT Standard Time"},
                        {"Europe/Helsinki", "FLE Standard Time"},
                        {"Europe/Isle_of_Man", "GMT Standard Time"},
                        {"Europe/Istanbul", "Turkey Standard Time"},
                        {"Europe/Jersey", "GMT Standard Time"},
                        {"Europe/Kaliningrad", "Kaliningrad Standard Time"},
                        {"Europe/Kiev", "FLE Standard Time"},
                        {"Europe/Kirov", "Russian Standard Time"},
                        {"Europe/Lisbon", "GMT Standard Time"},
                        {"Europe/Ljubljana", "Central Europe Standard Time"},
                        {"Europe/London", "GMT Standard Time"},
                        {"Europe/Luxembourg", "W. Europe Standard Time"},
                        {"Europe/Madrid", "Romance Standard Time"},
                        {"Europe/Malta", "W. Europe Standard Time"},
                        {"Europe/Mariehamn", "FLE Standard Time"},
                        {"Europe/Minsk", "Belarus Standard Time"},
                        {"Europe/Monaco", "W. Europe Standard Time"},
                        {"Europe/Moscow", "Russian Standard Time"},
                        {"Europe/Oslo", "W. Europe Standard Time"},
                        {"Europe/Paris", "Romance Standard Time"},
                        {"Europe/Podgorica", "Central Europe Standard Time"},
                        {"Europe/Prague", "Central Europe Standard Time"},
                        {"Europe/Riga", "FLE Standard Time"},
                        {"Europe/Rome", "W. Europe Standard Time"},
                        {"Europe/Samara", "Russia Time Zone 3"},
                        {"Europe/San_Marino", "W. Europe Standard Time"},
                        {"Europe/Sarajevo", "Central European Standard Time"},
                        {"Europe/Saratov", "Saratov Standard Time"},
                        {"Europe/Simferopol", "Russian Standard Time"},
                        {"Europe/Skopje", "Central European Standard Time"},
                        {"Europe/Sofia", "FLE Standard Time"},
                        {"Europe/Stockholm", "W. Europe Standard Time"},
                        {"Europe/Tallinn", "FLE Standard Time"},
                        {"Europe/Tirane", "Central Europe Standard Time"},
                        {"Europe/Tiraspol", "E. Europe Standard Time"},
                        {"Europe/Ulyanovsk", "Astrakhan Standard Time"},
                        {"Europe/Uzhgorod", "FLE Standard Time"},
                        {"Europe/Vaduz", "W. Europe Standard Time"},
                        {"Europe/Vatican", "W. Europe Standard Time"},
                        {"Europe/Vienna", "W. Europe Standard Time"},
                        {"Europe/Vilnius", "FLE Standard Time"},
                        {"Europe/Volgograd", "Volgograd Standard Time"},
                        {"Europe/Warsaw", "Central European Standard Time"},
                        {"Europe/Zagreb", "Central European Standard Time"},
                        {"Europe/Zaporozhye", "FLE Standard Time"},
                        {"Europe/Zurich", "W. Europe Standard Time"},
                        {"GB", "GMT Standard Time"},
                        {"GB-Eire", "GMT Standard Time"},
                        {"GMT+0", "UTC"},
                        {"GMT-0", "UTC"},
                        {"GMT0", "UTC"},
                        {"Greenwich", "UTC"},
                        {"Hongkong", "China Standard Time"},
                        {"Iceland", "Greenwich Standard Time"},
                        {"Indian/Antananarivo", "E. Africa Standard Time"},
                        {"Indian/Chagos", "Central Asia Standard Time"},
                        {"Indian/Christmas", "SE Asia Standard Time"},
                        {"Indian/Cocos", "Myanmar Standard Time"},
                        {"Indian/Comoro", "E. Africa Standard Time"},
                        {"Indian/Kerguelen", "West Asia Standard Time"},
                        {"Indian/Mahe", "Mauritius Standard Time"},
                        {"Indian/Maldives", "West Asia Standard Time"},
                        {"Indian/Mauritius", "Mauritius Standard Time"},
                        {"Indian/Mayotte", "E. Africa Standard Time"},
                        {"Indian/Reunion", "Mauritius Standard Time"},
                        {"Iran", "Iran Standard Time"},
                        {"Israel", "Israel Standard Time"},
                        {"Jamaica", "SA Pacific Standard Time"},
                        {"Japan", "Tokyo Standard Time"},
                        {"Kwajalein", "UTC+12"},
                        {"Libya", "Libya Standard Time"},
                        {"MST7MDT", "Mountain Standard Time"},
                        {"Mexico/BajaNorte", "Pacific Standard Time (Mexico)"},
                        {"Mexico/BajaSur", "Mountain Standard Time (Mexico)"},
                        {"Mexico/General", "Central Standard Time (Mexico)"},
                        {"NZ", "New Zealand Standard Time"},
                        {"NZ-CHAT", "Chatham Islands Standard Time"},
                        {"Navajo", "Mountain Standard Time"},
                        {"PRC", "China Standard Time"},
                        {"PST8PDT", "Pacific Standard Time"},
                        {"Pacific/Apia", "Samoa Standard Time"},
                        {"Pacific/Auckland", "New Zealand Standard Time"},
                        {"Pacific/Bougainville", "Bougainville Standard Time"},
                        {"Pacific/Chatham", "Chatham Islands Standard Time"},
                        {"Pacific/Easter", "Easter Island Standard Time"},
                        {"Pacific/Efate", "Central Pacific Standard Time"},
                        {"Pacific/Enderbury", "UTC+13"},
                        {"Pacific/Fakaofo", "UTC+13"},
                        {"Pacific/Fiji", "Fiji Standard Time"},
                        {"Pacific/Funafuti", "UTC+12"},
                        {"Pacific/Galapagos", "Central America Standard Time"},
                        {"Pacific/Gambier", "UTC-09"},
                        {"Pacific/Guadalcanal", "Central Pacific Standard Time"},
                        {"Pacific/Guam", "West Pacific Standard Time"},
                        {"Pacific/Honolulu", "Hawaiian Standard Time"},
                        {"Pacific/Johnston", "Hawaiian Standard Time"},
                        {"Pacific/Kiritimati", "Line Islands Standard Time"},
                        {"Pacific/Kosrae", "Central Pacific Standard Time"},
                        {"Pacific/Kwajalein", "UTC+12"},
                        {"Pacific/Majuro", "UTC+12"},
                        {"Pacific/Marquesas", "Marquesas Standard Time"},
                        {"Pacific/Midway", "UTC-11"},
                        {"Pacific/Nauru", "UTC+12"},
                        {"Pacific/Niue", "UTC-11"},
                        {"Pacific/Norfolk", "Norfolk Standard Time"},
                        {"Pacific/Noumea", "Central Pacific Standard Time"},
                        {"Pacific/Pago_Pago", "UTC-11"},
                        {"Pacific/Palau", "Tokyo Standard Time"},
                        {"Pacific/Pitcairn", "UTC-08"},
                        {"Pacific/Ponape", "Central Pacific Standard Time"},
                        {"Pacific/Port_Moresby", "West Pacific Standard Time"},
                        {"Pacific/Rarotonga", "Hawaiian Standard Time"},
                        {"Pacific/Saipan", "West Pacific Standard Time"},
                        {"Pacific/Samoa", "UTC-11"},
                        {"Pacific/Tahiti", "Hawaiian Standard Time"},
                        {"Pacific/Tarawa", "UTC+12"},
                        {"Pacific/Tongatapu", "Tonga Standard Time"},
                        {"Pacific/Truk", "West Pacific Standard Time"},
                        {"Pacific/Wake", "UTC+12"},
                        {"Pacific/Wallis", "UTC+12"},
                        {"Poland", "Central European Standard Time"},
                        {"Portugal", "GMT Standard Time"},
                        {"ROC", "Taipei Standard Time"},
                        {"ROK", "Korea Standard Time"},
                        {"Singapore", "Singapore Standard Time"},
                        {"Turkey", "Turkey Standard Time"},
                        {"UCT", "UTC"},
                        {"US/Alaska", "Alaskan Standard Time"},
                        {"US/Aleutian", "Aleutian Standard Time"},
                        {"US/Arizona", "US Mountain Standard Time"},
                        {"US/Central", "Central Standard Time"},
                        {"US/Eastern", "Eastern Standard Time"},
                        {"US/Hawaii", "Hawaiian Standard Time"},
                        {"US/Indiana-Starke", "Central Standard Time"},
                        {"US/Michigan", "Eastern Standard Time"},
                        {"US/Mountain", "Mountain Standard Time"},
                        {"US/Pacific", "Pacific Standard Time"},
                        {"US/Samoa", "UTC-11"},
                        {"UTC", "UTC"},
                        {"Universal", "UTC"},
                        {"W-SU", "Russian Standard Time"},
                        {"Zulu", "UTC"}};
#elif defined(_TD_DARWIN_64)
#include <errno.h>
#include <libproc.h>
#else
#include <argp.h>
#include <linux/sysctl.h>
#include <sys/file.h>
#include <sys/resource.h>
#include <sys/statvfs.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <unistd.h>
#endif

int32_t taosSetGlobalTimezone(const char *tz) {
  if (tz == NULL) {
    terrno = TSDB_CODE_INVALID_PARA;
    return terrno;
  }
  int32_t code = TSDB_CODE_SUCCESS;
  uDebug("[tz]set timezone to %s", tz)
#ifdef WINDOWS
  char winStr[TD_TIMEZONE_LEN * 2] = {0};
  for (size_t i = 0; i < W_TZ_CITY_NUM; i++) {
    if (strcmp(tz_win[i][0], tz) == 0) {
      char  keyPath[256] = {0};
      char  keyValue[100] = {0};
      DWORD keyValueSize = sizeof(keyValue);
      snprintf(keyPath, sizeof(keyPath), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones\\%s", tz_win[i][1]);
      RegGetValue(HKEY_LOCAL_MACHINE, keyPath, "Display", RRF_RT_ANY, NULL, (PVOID)&keyValue, &keyValueSize);
      if (keyValueSize > 0) {
        keyValue[4] = (keyValue[4] == '+' ? '-' : '+');
        keyValue[10] = 0;
        snprintf(winStr, sizeof(winStr), "TZ=%s:00", &(keyValue[1]));
      }
      break;
    }
  }

  _putenv(winStr);
  _tzset();
#else
  code = setenv("TZ", tz, 1);
  if (-1 == code) {
    terrno = TAOS_SYSTEM_ERROR(errno);
    return terrno;
  }

  tzset();
#endif

  time_t    tx1 = taosGetTimestampSec();
  return taosFormatTimezoneStr(tx1, tz, NULL, tsTimezoneStr);
}

int32_t taosGetLocalTimezoneOffset() {
  time_t    tx1 = taosGetTimestampSec();
  struct tm tm1;
  if (taosLocalTime(&tx1, &tm1, NULL, 0, NULL) == NULL) {
    uError("%s failed to get local time: code:%d", __FUNCTION__, errno);
    return TSDB_CODE_TIME_ERROR;
  }
#ifdef WINDOWS
  return -_timezone;
#else
  return (int32_t)(tm1.tm_gmtoff);
#endif
}

int32_t taosFormatTimezoneStr(time_t t, const char* tz, timezone_t sp, char *outTimezoneStr){
  struct tm tm1;
  if (taosLocalTime(&t, &tm1, NULL, 0, sp) == NULL) {
    uError("%s failed to get local time: code:%d", __FUNCTION__, errno);
    return TSDB_CODE_TIME_ERROR;
  }

  /*
   * format example:
   *
   * Asia/Shanghai (CST, +0800)
   * Europe/London (BST, +0100)
   * n/a (UTC, +0000)
   */

  char str1[TD_TIMEZONE_LEN] = {0};
  if (taosStrfTime(str1, sizeof(str1), "%Z", &tm1) == 0){
    uError("failed to get timezone name");
    return TSDB_CODE_TIME_ERROR;
  }

  char str2[TD_TIMEZONE_LEN] = {0};
  if (taosStrfTime(str2, sizeof(str2), "%z", &tm1) == 0){
    uError("failed to get timezone offset");
    return TSDB_CODE_TIME_ERROR;
  }
  (void)snprintf(outTimezoneStr, TD_TIMEZONE_LEN, "%s (%s, %s)", tz, str1, str2);
  uDebug("[tz] system timezone:%s", outTimezoneStr);
  return 0;
}

#ifndef WINDOWS
void getTimezoneStr(char *tz) {
  do {
    int n = readlink("/etc/localtime", tz, TD_TIMEZONE_LEN - 1);
    if (n < 0) {
      uWarn("[tz] failed to readlink /etc/localtime, reason:%s", strerror(errno));
      break;
    }

    char *zi = strstr(tz, "zoneinfo");
    if (zi == NULL) {
      uWarn("[tz] failed to find zoneinfo in /etc/localtime");
      break;
    }
    zi += sizeof("zoneinfo");
    memmove(tz, zi, TD_TIMEZONE_LEN - (zi - tz));
    goto END;
  } while (0);


  TdFilePtr pFile = taosOpenFile("/etc/timezone", TD_FILE_READ);
  if (pFile == NULL) {
    uWarn("[tz] failed to open /etc/timezone, reason:%s", strerror(errno));
    goto END;
  }
  int len = taosReadFile(pFile, tz, TD_TIMEZONE_LEN - 1);
  TAOS_UNUSED(taosCloseFile(&pFile));
  if (len <= 0) {
    uWarn("[tz] failed to read /etc/timezone, len:%d", len);
    goto END;
  }
  if (tz[len - 1] == '\n') {
    tz[len - 1] = '\0';
  }

END:
  if (tz[0] == '\0') {
    memcpy(tz, TZ_UNKNOWN, sizeof(TZ_UNKNOWN));
  }
  uDebug("[tz] system timezone:%s", tz);
}
#endif

int32_t taosGetSystemTimezone(char *outTimezoneStr) {
#ifdef WINDOWS
  char  value[100] = {0};
  char  keyPath[100] = {0};
  DWORD bufferSize = sizeof(value);
  LONG result = RegGetValue(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\TimeZoneInformation", "TimeZoneKeyName",
              RRF_RT_ANY, NULL, (PVOID)&value, &bufferSize);
  if (result != ERROR_SUCCESS) {
    return TAOS_SYSTEM_WINAPI_ERROR(result);
  }
  if (bufferSize > 0) {
    for (size_t i = 0; i < W_TZ_NUM; i++) {
      if (strcmp(win_tz[i][0], value) == 0) {
        tstrncpy(outTimezoneStr, win_tz[i][1], TD_TIMEZONE_LEN);
        bufferSize = sizeof(value);
        snprintf(keyPath, sizeof(keyPath), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones\\%s", value);
        result = RegGetValue(HKEY_LOCAL_MACHINE, keyPath, "Display", RRF_RT_ANY, NULL, (PVOID)&value, &bufferSize);
        if (result != ERROR_SUCCESS) {
          return TAOS_SYSTEM_WINAPI_ERROR(result);
        }
        if (bufferSize > 0) {     // value like (UTC+05:30) Chennai, Kolkata, Mumbai, New Delhi
          snprintf(outTimezoneStr, TD_TIMEZONE_LEN, "%s (UTC, %c%c%c%c%c)", outTimezoneStr,
                   value[4], value[5], value[6], value[8], value[9]);
        }
        break;
      }
    }
  }
  return 0;
#else
  char tz[TD_TIMEZONE_LEN] = {0};
  getTimezoneStr(tz);
  time_t    tx1 = taosGetTimestampSec();
  return taosFormatTimezoneStr(tx1, tz, NULL, outTimezoneStr);
#endif
}