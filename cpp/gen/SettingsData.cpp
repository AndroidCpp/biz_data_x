#include "SettingsData.hpp"
#include <QDebug>
#include <quuid.h>

// keys of QVariantMap used in this APP
static const QString idKey = "id";
static const QString versionKey = "version";
static const QString isProductionEnvironmentKey = "isProductionEnvironment";
static const QString primaryColorKey = "primaryColor";
static const QString accentColorKey = "accentColor";
static const QString darkThemeKey = "darkTheme";
static const QString hasPublicCacheKey = "hasPublicCache";
static const QString useCompactJsonFormatKey = "useCompactJsonFormat";
static const QString lastUsedNumberKey = "lastUsedNumber";

// keys used from Server API etc
static const QString idForeignKey = "id";
static const QString versionForeignKey = "version";
static const QString isProductionEnvironmentForeignKey = "isProductionEnvironment";
static const QString primaryColorForeignKey = "primaryColor";
static const QString accentColorForeignKey = "accentColor";
static const QString darkThemeForeignKey = "darkTheme";
static const QString hasPublicCacheForeignKey = "hasPublicCache";
static const QString useCompactJsonFormatForeignKey = "useCompactJsonFormat";
static const QString lastUsedNumberForeignKey = "lastUsedNumber";

/*
 * Default Constructor if SettingsData not initialized from QVariantMap
 */
SettingsData::SettingsData(QObject *parent) :
        QObject(parent), mId(-1), mVersion(0), mIsProductionEnvironment(false), mPrimaryColor(0), mAccentColor(0), mDarkTheme(false), mHasPublicCache(false), mUseCompactJsonFormat(false), mLastUsedNumber(0)
{
}

/*
 * initialize SettingsData from QVariantMap
 * Map got from JsonDataAccess or so
 * includes also transient values
 * uses own property names
 * corresponding export method: toMap()
 */
void SettingsData::fillFromMap(const QVariantMap& settingsDataMap)
{
	mId = settingsDataMap.value(idKey).toInt();
	mVersion = settingsDataMap.value(versionKey).toInt();
	mIsProductionEnvironment = settingsDataMap.value(isProductionEnvironmentKey).toBool();
	mPrimaryColor = settingsDataMap.value(primaryColorKey).toInt();
	mAccentColor = settingsDataMap.value(accentColorKey).toInt();
	mDarkTheme = settingsDataMap.value(darkThemeKey).toBool();
	mHasPublicCache = settingsDataMap.value(hasPublicCacheKey).toBool();
	mUseCompactJsonFormat = settingsDataMap.value(useCompactJsonFormatKey).toBool();
	mLastUsedNumber = settingsDataMap.value(lastUsedNumberKey).toInt();
}
/*
 * initialize OrderData from QVariantMap
 * Map got from JsonDataAccess or so
 * includes also transient values
 * uses foreign property names - per ex. from Server API
 * corresponding export method: toForeignMap()
 */
void SettingsData::fillFromForeignMap(const QVariantMap& settingsDataMap)
{
	mId = settingsDataMap.value(idForeignKey).toInt();
	mVersion = settingsDataMap.value(versionForeignKey).toInt();
	mIsProductionEnvironment = settingsDataMap.value(isProductionEnvironmentForeignKey).toBool();
	mPrimaryColor = settingsDataMap.value(primaryColorForeignKey).toInt();
	mAccentColor = settingsDataMap.value(accentColorForeignKey).toInt();
	mDarkTheme = settingsDataMap.value(darkThemeForeignKey).toBool();
	mHasPublicCache = settingsDataMap.value(hasPublicCacheForeignKey).toBool();
	mUseCompactJsonFormat = settingsDataMap.value(useCompactJsonFormatForeignKey).toBool();
	mLastUsedNumber = settingsDataMap.value(lastUsedNumberForeignKey).toInt();
}
/*
 * initialize OrderData from QVariantMap
 * Map got from JsonDataAccess or so
 * excludes transient values
 * uses own property names
 * corresponding export method: toCacheMap()
 */
void SettingsData::fillFromCacheMap(const QVariantMap& settingsDataMap)
{
	mId = settingsDataMap.value(idKey).toInt();
	mVersion = settingsDataMap.value(versionKey).toInt();
	mIsProductionEnvironment = settingsDataMap.value(isProductionEnvironmentKey).toBool();
	mPrimaryColor = settingsDataMap.value(primaryColorKey).toInt();
	mAccentColor = settingsDataMap.value(accentColorKey).toInt();
	mDarkTheme = settingsDataMap.value(darkThemeKey).toBool();
	mHasPublicCache = settingsDataMap.value(hasPublicCacheKey).toBool();
	mUseCompactJsonFormat = settingsDataMap.value(useCompactJsonFormatKey).toBool();
	mLastUsedNumber = settingsDataMap.value(lastUsedNumberKey).toInt();
}

void SettingsData::prepareNew()
{
}

/*
 * Checks if all mandatory attributes, all DomainKeys and uuid's are filled
 */
bool SettingsData::isValid()
{
	if (mId == -1) {
		return false;
	}
	return true;
}
	
/*
 * Exports Properties from SettingsData as QVariantMap
 * exports ALL data including transient properties
 * To store persistent Data in JsonDataAccess use toCacheMap()
 */
QVariantMap SettingsData::toMap()
{
	QVariantMap settingsDataMap;
	settingsDataMap.insert(idKey, mId);
	settingsDataMap.insert(versionKey, mVersion);
	settingsDataMap.insert(isProductionEnvironmentKey, mIsProductionEnvironment);
	settingsDataMap.insert(primaryColorKey, mPrimaryColor);
	settingsDataMap.insert(accentColorKey, mAccentColor);
	settingsDataMap.insert(darkThemeKey, mDarkTheme);
	settingsDataMap.insert(hasPublicCacheKey, mHasPublicCache);
	settingsDataMap.insert(useCompactJsonFormatKey, mUseCompactJsonFormat);
	settingsDataMap.insert(lastUsedNumberKey, mLastUsedNumber);
	return settingsDataMap;
}

/*
 * Exports Properties from SettingsData as QVariantMap
 * To send data as payload to Server
 * Makes it possible to use defferent naming conditions
 */
QVariantMap SettingsData::toForeignMap()
{
	QVariantMap settingsDataMap;
	settingsDataMap.insert(idForeignKey, mId);
	settingsDataMap.insert(versionForeignKey, mVersion);
	settingsDataMap.insert(isProductionEnvironmentForeignKey, mIsProductionEnvironment);
	settingsDataMap.insert(primaryColorForeignKey, mPrimaryColor);
	settingsDataMap.insert(accentColorForeignKey, mAccentColor);
	settingsDataMap.insert(darkThemeForeignKey, mDarkTheme);
	settingsDataMap.insert(hasPublicCacheForeignKey, mHasPublicCache);
	settingsDataMap.insert(useCompactJsonFormatForeignKey, mUseCompactJsonFormat);
	settingsDataMap.insert(lastUsedNumberForeignKey, mLastUsedNumber);
	return settingsDataMap;
}


/*
 * Exports Properties from SettingsData as QVariantMap
 * transient properties are excluded:
 * To export ALL data use toMap()
 */
QVariantMap SettingsData::toCacheMap()
{
	// no transient properties found from data model
	// use default toMao()
	return toMap();
}
// ATT 
// Mandatory: id
// Domain KEY: id
int SettingsData::id() const
{
	return mId;
}

void SettingsData::setId(int id)
{
	if (id != mId) {
		mId = id;
		emit idChanged(id);
	}
}
// ATT 
// Optional: version
int SettingsData::version() const
{
	return mVersion;
}

void SettingsData::setVersion(int version)
{
	if (version != mVersion) {
		mVersion = version;
		emit versionChanged(version);
	}
}
// ATT 
// Optional: isProductionEnvironment
bool SettingsData::isProductionEnvironment() const
{
	return mIsProductionEnvironment;
}

void SettingsData::setIsProductionEnvironment(bool isProductionEnvironment)
{
	if (isProductionEnvironment != mIsProductionEnvironment) {
		mIsProductionEnvironment = isProductionEnvironment;
		emit isProductionEnvironmentChanged(isProductionEnvironment);
	}
}
// ATT 
// Optional: primaryColor
int SettingsData::primaryColor() const
{
	return mPrimaryColor;
}

void SettingsData::setPrimaryColor(int primaryColor)
{
	if (primaryColor != mPrimaryColor) {
		mPrimaryColor = primaryColor;
		emit primaryColorChanged(primaryColor);
	}
}
// ATT 
// Optional: accentColor
int SettingsData::accentColor() const
{
	return mAccentColor;
}

void SettingsData::setAccentColor(int accentColor)
{
	if (accentColor != mAccentColor) {
		mAccentColor = accentColor;
		emit accentColorChanged(accentColor);
	}
}
// ATT 
// Optional: darkTheme
bool SettingsData::darkTheme() const
{
	return mDarkTheme;
}

void SettingsData::setDarkTheme(bool darkTheme)
{
	if (darkTheme != mDarkTheme) {
		mDarkTheme = darkTheme;
		emit darkThemeChanged(darkTheme);
	}
}
// ATT 
// Optional: hasPublicCache
bool SettingsData::hasPublicCache() const
{
	return mHasPublicCache;
}

void SettingsData::setHasPublicCache(bool hasPublicCache)
{
	if (hasPublicCache != mHasPublicCache) {
		mHasPublicCache = hasPublicCache;
		emit hasPublicCacheChanged(hasPublicCache);
	}
}
// ATT 
// Optional: useCompactJsonFormat
bool SettingsData::useCompactJsonFormat() const
{
	return mUseCompactJsonFormat;
}

void SettingsData::setUseCompactJsonFormat(bool useCompactJsonFormat)
{
	if (useCompactJsonFormat != mUseCompactJsonFormat) {
		mUseCompactJsonFormat = useCompactJsonFormat;
		emit useCompactJsonFormatChanged(useCompactJsonFormat);
	}
}
// ATT 
// Optional: lastUsedNumber
int SettingsData::lastUsedNumber() const
{
	return mLastUsedNumber;
}

void SettingsData::setLastUsedNumber(int lastUsedNumber)
{
	if (lastUsedNumber != mLastUsedNumber) {
		mLastUsedNumber = lastUsedNumber;
		emit lastUsedNumberChanged(lastUsedNumber);
	}
}


SettingsData::~SettingsData()
{
	// place cleanUp code here
}
	
