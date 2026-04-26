/*
 * Copyright (C) the Wine project
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_XSTORE_H
#define __WINE_XSTORE_H

typedef void *XStoreContextHandle;
typedef void *XStoreLicenseHandle;
typedef void *XStoreProductQueryHandle;

typedef enum XStoreCanLicenseStatus XStoreCanLicenseStatus;
typedef enum XStoreDurationUnit XStoreDurationUnit;
typedef enum XStoreProductKind XStoreProductKind;

typedef struct XStoreAddonLicense XStoreAddonLicense;
typedef struct XStoreAvailability XStoreAvailability;
typedef struct XStoreCanAcquireLicenseResult XStoreCanAcquireLicenseResult;
typedef struct XStoreCollectionData XStoreCollectionData;
typedef struct XStoreConsumableResult XStoreConsumableResult;
typedef struct XStoreGameLicense XStoreGameLicense;
typedef struct XStoreImage XStoreImage;
typedef struct XStorePackageUpdate XStorePackageUpdate;
typedef struct XStorePrice XStorePrice;
typedef struct XStoreProduct XStoreProduct;
typedef struct XStoreRateAndReviewResult XStoreRateAndReviewResult;
typedef struct XStoreSku XStoreSku;
typedef struct XStoreSubscriptionInfo XStoreSubscriptionInfo;
typedef struct XStoreVideo XStoreVideo;

typedef void    __stdcall XStoreGameLicenseChangedCallback( void *context );
typedef void    __stdcall XStorePackageLicenseLostCallback( void *context );
typedef BOOLEAN __stdcall XStoreProductQueryCallback( const XStoreProduct *product, void *context );

enum XStoreCanLicenseStatus
{
    XStoreCanLicenseStatus_NotLicensableToUser,
    XStoreCanLicenseStatus_Licensable,
    XStoreCanLicenseStatus_LicenseActionNotApplicableToProduct,
};

enum XStoreDurationUnit
{
    XStoreDurationUnit_Minute,
    XStoreDurationUnit_Hour,
    XStoreDurationUnit_Day,
    XStoreDurationUnit_Week,
    XStoreDurationUnit_Month,
    XStoreDurationUnit_Year,
};

enum XStoreProductKind
{
    XStoreProductKind_None                  = 0x00,
    XStoreProductKind_Consumable            = 0x01,
    XStoreProductKind_Durable               = 0x02,
    XStoreProductKind_Game                  = 0x04,
    XStoreProductKind_Pass                  = 0x08,
    XStoreProductKind_UnmanagedConsumable   = 0x10
};

struct XStoreAddonLicense
{
    char skuStoreId[18];
    char inAppOfferToken[64];
    BOOLEAN isActive;
    time_t expirationDate;
};

struct XStorePrice
{
    float basePrice;
    float price;
    float recurrencePrice;
    const char *currencyCode;
    char formattedBasePrice[16];
    char formattedPrice[16];
    char formattedRecurrencePrice[16];
    BOOLEAN isOnSale;
    time_t saleEndDate;
};

struct XStoreAvailability
{
    const char *availabilityId;
    XStorePrice price;
    time_t endDate;
};

struct XStoreCanAcquireLicenseResult
{
    char licensableSku[5];
    XStoreCanLicenseStatus status;
};

struct XStoreCollectionData
{
    time_t acquiredDate;
    time_t startDate;
    time_t endDate;
    BOOLEAN isTrial;
    UINT32 trialTimeRemainingInSeconds;
    UINT32 quantity;
    const char *campaignId;
    const char *developerOfferId;
};

struct XStoreConsumableResult
{
    UINT32 quantity;
};

struct XStoreGameLicense
{
    char skuStoreId[18];
    BOOLEAN isActive;
    BOOLEAN isTrialOwnedByThisUser;
    BOOLEAN isDiscLicense;
    BOOLEAN isTrial;
    UINT32 trialTimeRemainingInSeconds;
    char trialUniqueId[64];
    time_t expirationDate;
};

struct XStoreImage
{
    const char *uri;
    UINT32 height;
    UINT32 width;
    const char *caption;
    const char *imagePurposeTag;
};

struct XStorePackageUpdate
{
    char packageIdentifier[33];
    BOOLEAN isMandatory;
};

struct XStoreProduct
{
    const char *storeId;
    const char *title;
    const char *description;
    const char *language;
    const char *inAppOfferToken;
    char *linkUri;
    XStoreProductKind productKind;
    XStorePrice price;
    BOOLEAN hasDigitalDownload;
    BOOLEAN isInUserCollection;
    UINT32 keywordsCount;
    const char **keywords;
    UINT32 skusCount;
    XStoreSku *skus;
    UINT32 imagesCount;
    XStoreImage *images;
    UINT32 videosCount;
    XStoreVideo *videos;
};

struct XStoreRateAndReviewResult
{
    BOOLEAN wasUpdated;
};

struct XStoreSubscriptionInfo
{
    BOOLEAN hasTrialPeriod;
    XStoreDurationUnit trialPeriodUnit;
    UINT32 trialPeriod;
    XStoreDurationUnit billingPeriodUnit;
    UINT32 billingPeriod;
};

struct XStoreSku
{
    const char *skuId;
    const char *title;
    const char *description;
    const char *language;
    XStorePrice price;
    BOOLEAN isTrial;
    BOOLEAN isInUserCollection;
    XStoreCollectionData collectionData;
    BOOLEAN isSubscription;
    XStoreSubscriptionInfo subscriptionInfo;
    UINT32 bundledSkusCount;
    const char **bundledSkus;
    UINT32 imagesCount;
    XStoreImage *images;
    UINT32 videosCount;
    XStoreVideo *videos;
    UINT32 availabilitiesCount;
    XStoreAvailability *availabilities;
};

struct XStoreVideo
{
    const char *uri;
    UINT32 height;
    UINT32 width;
    const char *caption;
    const char *videoPurposeTag;
    XStoreImage previewImage;
};

#endif
