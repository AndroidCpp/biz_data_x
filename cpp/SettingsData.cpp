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

// keys used from Server API etc
static const QString idForeignKey = "id";
static const QString versionForeignKey = "version";
static const QString isProductionEnvironmentForeignKey = "isProductionEnvironment";
static const QString primaryColorForeignKey = "primaryColor";
static const QString accentColorForeignKey = "accentColor";
static const QString darkThemeForeignKey = "darkTheme";

/*
 * Default Constructor if SettingsData not initialized from QVariantMap
 */
SettingsData::SettingsData(QObject *parent) :
        QObject(parent), mId(-1), mVersion(0), mIsProductionEnvironment(false), mPrimaryColor(0), mAccentColor(0), mDarkTheme(false)
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


SettingsData::~SettingsData()
{
	// place cleanUp code here
}
	
