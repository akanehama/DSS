#include <stdafx.h>
#include "SetUILanguage.h"
#include "Registry.h"
#include <VersionHelpers.h>

/* ------------------------------------------------------------------- */


void	SetUILanguage(LANGID LangID)
{
	if (IsWindowsVistaOrGreater())
	{
		// Vista specific
		typedef LANGID (WINAPI * SetThreadUILanguageProc)(LANGID);
		typedef LANGID (WINAPI * SetThreadPreferredUILanguagesProc)(DWORD, PCWSTR, PULONG);

		SetThreadUILanguageProc				SetThreadUILanguage;
		SetThreadPreferredUILanguagesProc	SetThreadPreferredUILanguages;

//		const UINT MUI_LANGUAGE_NAME	= 0x8; // Use ISO language (culture) name convention
//		const UINT MUI_THREAD_LANGUAGES = 0x40; // GetThreadPreferredUILanguages merges in thread preferred languages

		SetThreadPreferredUILanguages = 
			(SetThreadPreferredUILanguagesProc)GetProcAddress(
				GetModuleHandle(_T("kernel32.dll")),
				"SetThreadPreferredUILanguages");
		if (SetThreadPreferredUILanguages)
		{
			// Set the preferred languages
			WCHAR			szPrefLanguages[2000];
			WCHAR *			szEnglish = L"en-US";
			WCHAR *			szFrench  = L"fr-FR";
			WCHAR *			szCzech   = L"cs-CZ";
			WCHAR *			szSpanish = L"es-ES";
			WCHAR *			szItalian = L"it-IT";
			WCHAR *			szCatalan = L"ca-ES";	// Catalan - Espana
			WCHAR *			szGerman  = L"de-DE";
			WCHAR *			szDutch   = L"nl-NL";
			WCHAR *			szChinese = L"zh-TW";	// Traditional Chinese or zh-Hant
			//WCHAR *			szChinese = L"zh-CN";	// Simplified Chinese or zh-Hans
			WCHAR *			szPortuguese = L"pt-BR";	// Portuguese/Brazilian
			WCHAR *			szRomanian = L"ro-RO";	// Romanian
			WCHAR *			szRussian = L"ru-RU";	// Russian
			WCHAR *			szTurkish = L"tr-TR";	// Turkish
			WCHAR *			szJapanese = L"ja-JP";	// Japanese
			ULONG			lNumLang = 5;

			WCHAR *			szLang1;
			WCHAR *			szLang2;
			WCHAR *			szLang3;
			WCHAR *			szLang4;
			WCHAR *			szLang5;

			switch (PRIMARYLANGID(LangID))
			{
				case LANG_FRENCH :
					szLang1 = szFrench;
					szLang2 = szEnglish;
					szLang3 = szSpanish;
					szLang4 = szItalian;
					szLang5 = szCzech;
					break;
				case LANG_SPANISH :
					szLang1 = szSpanish;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szItalian;
					szLang5 = szCzech;
					break;
				case LANG_ENGLISH :
					szLang1 = szEnglish;
					szLang2 = szFrench;
					szLang3 = szSpanish;
					szLang4 = szItalian;
					szLang5 = szCzech;
					break;
				case LANG_GERMAN :
					szLang1 = szGerman;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szSpanish;
					szLang5 = szItalian;
					break;
				case LANG_DUTCH :
					szLang1 = szDutch;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szGerman;
					szLang5 = szItalian;
					break;
				case LANG_CZECH :
					szLang1 = szCzech;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szSpanish;
					szLang5 = szItalian;
					break;
				case LANG_ITALIAN :
					szLang1 = szItalian;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szSpanish;
					szLang5 = szCzech;
					break;
				case LANG_CATALAN :
					szLang1 = szCatalan;
					szLang2 = szSpanish;
					szLang3 = szFrench;
					szLang4 = szEnglish;
					szLang5 = szItalian;
					break;
				case LANG_CHINESE :
					szLang1 = szChinese;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szSpanish;
					szLang5 = szItalian;
					break;
				case LANG_PORTUGUESE :
					szLang1 = szPortuguese;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szSpanish;
					szLang5 = szItalian;
					break;
				case LANG_ROMANIAN :
					szLang1 = szRomanian;
					szLang2 = szFrench;
					szLang3 = szEnglish;
					szLang4 = szSpanish;
					szLang5 = szItalian;
					break;
				case LANG_RUSSIAN :
					szLang1 = szRussian;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szSpanish;
					szLang5 = szItalian;
					break;
				case LANG_TURKISH :
					szLang1 = szTurkish;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szSpanish;
					szLang5 = szItalian;
					break;
				case LANG_JAPANESE:
					szLang1 = szJapanese;
					szLang2 = szEnglish;
					szLang3 = szFrench;
					szLang4 = szSpanish;
					szLang5 = szItalian;
					break;
			};

			WCHAR *			szPtr = szPrefLanguages;
			memcpy(szPtr, szLang1, sizeof(WCHAR)*6);
			szPtr += 6;
			memcpy(szPtr, szLang2, sizeof(WCHAR)*6);
			szPtr += 6;
			memcpy(szPtr, szLang3, sizeof(WCHAR)*6);
			szPtr += 6;
			memcpy(szPtr, szLang4, sizeof(WCHAR)*6);
			szPtr += 6;
			memcpy(szPtr, szLang5, sizeof(WCHAR)*6);
			szPtr += 6;
			*szPtr = 0;

			SetThreadPreferredUILanguages(MUI_LANGUAGE_NAME/* | MUI_THREAD_LANGUAGES*/, szPrefLanguages, &lNumLang);
		};
		SetThreadUILanguage = (SetThreadUILanguageProc)GetProcAddress(
			GetModuleHandle(_T("kernel32.dll")),
			"SetThreadUILanguage");
		if (SetThreadUILanguage)
			SetThreadUILanguage(LangID);
	}
	else
		SetThreadLocale(MAKELCID(LangID,SORT_DEFAULT));
};

/* ------------------------------------------------------------------- */

/*
typedef enum tagDSSLANGUAGE
{
	DSSL_DEFAULT		= 0,
	DSSL_FRENCH			= 1,
	DSSL_ENGLISH		= 2,
	DSSL_SPANISH		= 3,
	DSSL_CZECH			= 4,
	DSSL_ITALIAN		= 5,
	DSSL_DUTCH			= 6,
	DSSL_CATALAN		= 7,
	DSSL_GERMAN			= 8,
	DSSL_CHINESE		= 9,
	DSSL_PORTUGUESE		= 10,
	DSSL_ROMANIAN		= 11,
	DSSL_RUSSIAN		= 12,
	DSSL_TURKISH		= 13,
	DSSL_JAPANESE		= 14
} DSSLANGUAGE;
------------------------------------------------------------------- */

;

/* ------------------------------------------------------------------- */
