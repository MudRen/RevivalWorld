/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : material.h
 * Author : Clode@RevivalWorld
 * Date   : 
 * Note   : INCLUDE file
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#define MATERIAL_CHINESE	([ \
METAL	:	"[1;37mª÷ÄÝ[0m",	\
STONE	:	"[0;1;30m­ì¥Û[0m",	\
WATER	:	"[1;36m²M¤ô[0m", 	\
WOOD	:	"[0;33m­ì¤ì[0m", 	\
FUEL	:	"[1;34m¿U®Æ[0m", 	\
GOLD	:	"[1;33mª÷[0m", 	\
IRON	:	"[1;37mÅK[0m",	\
])

/* °ò¥»­ì®Æ */
#define METAL		"metal"		//ª÷ÄÝ
#define WATER		"water"		//¤ô
#define WOOD		"wood"		//­ì¤ì
#define STONE		"stone"		//­ì¥Û
#define FUEL		"fuel"		//¤Æ¥Û¿U®Æ

#define GOLD		"gold"		//¶Àª÷
#define IRON		"iron"		//ÅK

#define MATERIAL(x)	("/obj/materials/"+x)

// ¤@¯Å­ì®Æ
#define M_METAL		"metal"		//ª÷ÄÝ
#define M_STONE		"stone"		//¥Û§÷
#define M_WOOD		"wood"		//­ì¤ì
#define M_WATER		"water"		//¤ô
#define M_FUEL		"fuel"		//¿U®Æ

// ¤G¯Å­ì®Æ
// ª÷ÄÝ
#define M_GOLD		"gold"		//ª÷
#define M_COPPER	"copper"	//»É
#define M_SILVER	"silver"	//»È
#define M_TIN		"tinmine"	//¿ü
#define M_ALUMINUM	"aluminum"	//¾T
#define M_IRON		"iron"		//ÅK
#define M_URANIUM	"uranium"	//¹\
// ¥Û§÷
#define M_QUARTZ	"quartz"	//¥Û­^
#define M_SILICON	"silicon"	//ª¿¬â
#define M_POTTER	"potter"	//³³¤g
#define M_MARBLE	"marble"	//¤j²z¥Û
#define M_GRANITE	"granite"	//ªá±^©¥
#define M_SERPENTINE 	"serpentine"	//³D¯¾©¥
#define M_DIAMOND	"diamond"	//Æp¥Û
#define M_LIME		"lime"		//¥Û¦Ç©¥
// ­ì¤ì
#define M_FIR		"fir"		//§ü¤ì
#define M_JUNIPER	"juniper"	//ÀÌ¤ì
#define M_SANDAL	"sandal"	//ÀÈ¤ì
#define M_TEAK		"teak"		//¬c¤ì
// ¿U®Æ
#define M_OIL		"oil"		//­ìªo
#define M_GAS		"ngas"		//¤ÑµM®ð
#define M_COAL		"coal"		//·ÑÄq
// ¤ô
#define M_ROWATER	"rowater"	//°fº¯³z¤ô
#define M_DIWATER	"diwater"	//¥hÂ÷¤l¤ô
#define M_DTWATER	"dtwater"	//»]ÃH¤ô

// ¤T¯Å­ì®Æ
#define M_STEEL		"steel"		//¿û
#define M_PLASTICS	"plastics"	//¶ì½¦
#define M_RUBBER	"rubber"	//¾ó½¦
#define M_GLASS		"glass"		//¬Á¼þ
