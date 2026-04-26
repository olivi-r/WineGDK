/*
 * Xbox Game runtime Library
 *
 * Copyright 2026 Olivia Ryan
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

#include <wtypes.h>
#include <xgameruntime.h>

HRESULT WINAPI XStoreAcquireLicenseForDurablesAsync( const XStoreContextHandle storeContextHandle, const char *storeId, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreAcquireLicenseForDurablesResult( XAsyncBlock *async, XStoreLicenseHandle *storeLicenseHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreAcquireLicenseForPackageAsync( const XStoreProductQueryHandle productQueryHandle, const char *packageIdentifier, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreAcquireLicenseForPackageResult( XAsyncBlock *async, XStoreLicenseHandle *storeLicenseHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreCanAcquireLicenseForPackageAsync( const XStoreContextHandle storeContextHandle, const char *packageIdentifier, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreCanAcquireLicenseForPackageResult( XAsyncBlock *async, XStoreCanAcquireLicenseResult *storeCanAcquireLicense )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreCanAcquireLicenseForStoreIdAsync( const XStoreContextHandle storeContextHandle, const char *storeProductId, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreCanAcquireLicenseForStoreIdResult( XAsyncBlock *async, XStoreCanAcquireLicenseResult *storeCanAcquireLicense )
{
    return E_NOTIMPL;
}

void WINAPI XStoreCloseContextHandle( XStoreContextHandle storeContextHandle )
{
}

void WINAPI XStoreCloseLicenseHandle( XStoreLicenseHandle storeLicenseHandle )
{
}

void WINAPI XStoreCloseProductsQueryHandle( XStoreProductQueryHandle productQueryHandle )
{
}

HRESULT WINAPI XStoreCreateContext( const XUserHandle user, XStoreContextHandle *storeContextHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreDownloadAndInstallPackagesAsync( const XStoreContextHandle storeContextHandle, const char **storeIds, SIZE_T storeIdsCount, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreDownloadAndInstallPackagesResult( XAsyncBlock *async, UINT32 count, char **packageIdentifiers )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreDownloadAndInstallPackagesResultCount( XAsyncBlock *async, UINT32 *count )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreDownloadAndInstallPackageUpdatesAsync( const XStoreContextHandle storeContextHandle, const char **packageIdentifiers, SIZE_T packageIdentifiersCount, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreDownloadAndInstallPackageUpdatesResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreDownloadPackageUpdatesAsync( const XStoreContextHandle storeContextHandle, const char **packageIdentifiers, SIZE_T packageIdentifiersCount, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreDownloadPackageUpdatesResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreEnumerateProductsQuery( const XStoreProductQueryHandle productQueryHandle, void *context, XStoreProductQueryCallback *callback )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreGetUserCollectionsIdAsync( const XStoreContextHandle storeContextHandle, const char *serviceTicket, const char *publisherUserId, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreGetUserCollectionsIdResult( XAsyncBlock *async, SIZE_T size, char *result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreGetUserCollectionsIdResultSize( XAsyncBlock *async, SIZE_T *size )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreGetUserPurchaseIdAsync( const XStoreContextHandle storeContextHandle, const char *serviceTicket, const char *publisherUserId, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreGetUserPurchaseIdResult( XAsyncBlock *async, SIZE_T size, char *result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreGetUserPurchaseIdResultSize( XAsyncBlock *async, SIZE_T *size )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XStoreIsAvailabilityPurchasable( const XStoreAvailability availability )
{
    return FALSE;
}

BOOLEAN WINAPI XStoreIsLicenseValid( const XStoreLicenseHandle storeLicenseHandle )
{
    return FALSE;
}

BOOLEAN WINAPI XStoreProductsQueryHasMorePages( const XStoreProductQueryHandle productQueryHandle )
{
    return FALSE;
}

HRESULT WINAPI XStoreProductsQueryNextPageAsync( const XStoreProductQueryHandle productQueryHandle, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreProductsQueryNextPageResult( XAsyncBlock *async, XStoreProductQueryHandle *productQueryHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryAddOnLicensesAsync( const XStoreContextHandle storeContextHandle, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryAddOnLicensesResult( XAsyncBlock *async, UINT32 count, XStoreAddonLicense *addOnLicenses)
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryAddOnLicensesResultCount( XAsyncBlock *async, UINT32 *count )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryAssociatedProductsAsync( const XStoreContextHandle storeContextHandle, XStoreProductKind productKinds, UINT32 maxItemsToRetrievePerPage, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryAssociatedProductsForStoreIdAsync( const XStoreContextHandle storeContextHandle, const char *storeId, XStoreProductKind productKinds, UINT32 maxItemsToRetrievePerPage, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryAssociatedProductsForStoreIdResult( XAsyncBlock *async, XStoreProductQueryHandle *productQueryHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryAssociatedProductsResult( XAsyncBlock *async, XStoreProductQueryHandle *productQueryHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryConsumableBalanceRemainingAsync( const XStoreContextHandle storeContextHandle, const char *storeProductId, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryConsumableBalanceRemainingResult( XAsyncBlock *async, XStoreConsumableResult *consumableResult )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryEntitledProductsAsync( const XStoreContextHandle storeContextHandle, XStoreProductKind productKinds, UINT32 maxItemsToRetrievePerPage, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryEntitledProductsResult( XAsyncBlock *async, XStoreProductQueryHandle *productQueryHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryGameAndDlcPackageUpdatesAsync( const XStoreContextHandle storeContextHandle, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryGameAndDlcPackageUpdatesResult( XAsyncBlock *async, UINT32 count, XStorePackageUpdate *packageUpdates)
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryGameAndDlcPackageUpdatesResultCount( XAsyncBlock *async, UINT32 *count )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryGameLicenseAsync( const XStoreContextHandle storeContextHandle, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryGameLicenseResult( XAsyncBlock *async, XStoreGameLicense *license )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryLicenseTokenAsync( const XStoreContextHandle storeContextHandle, const char **productIds, SIZE_T productIdsCount, const char *customDeveloperString, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryLicenseTokenResult( XAsyncBlock *async, SIZE_T size, char *result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryLicenseTokenResultSize( XAsyncBlock *async, SIZE_T *size )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryPackageIdentifier( const char *storeId, SIZE_T size, char *packageIdentifier )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryPackageUpdatesAsync( XStoreContextHandle storeContextHandle, const char **packageIdentifiers, SIZE_T packageIdentifiersCount, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryPackageUpdatesResult( XAsyncBlock *async, UINT32 count, XStorePackageUpdate *packageUpdates)
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryPackageUpdatesResultCount( XAsyncBlock *async, UINT32 *count )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryProductForCurrentGameAsync( const XStoreContextHandle storeContextHandle, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryProductForCurrentGameResult( XAsyncBlock *async, XStoreProductQueryHandle *productQueryHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryProductForPackageAsync( const XStoreContextHandle storeContextHandle, XStoreProductKind productKinds, const char *packageIdentifier, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryProductForPackageResult( XAsyncBlock *async, XStoreProductQueryHandle *productQueryHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryProductsAsync( const XStoreContextHandle storeContextHandle, XStoreProductKind productKinds, const char **storeIds, SIZE_T storeIdsCount, const char **actionFilters, SIZE_T actionFiltersCount, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreQueryProductsResult( XAsyncBlock *async, XStoreProductQueryHandle *productQueryHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreRegisterGameLicenseChanged( XStoreContextHandle storeContextHandle, XTaskQueueHandle queue, void *context, XStoreGameLicenseChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreRegisterPackageLicenseLost( XStoreLicenseHandle licenseHandle, XTaskQueueHandle queue, void *context, XStorePackageLicenseLostCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreReportConsumableFulfillmentAsync( const XStoreContextHandle storeContextHandle, const char *storeProductId, UINT32 quantity, GUID trackingId, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreReportConsumableFulfillmentResult( XAsyncBlock *async, XStoreConsumableResult *consumableResult )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowAssociatedProductsUIAsync( const XStoreContextHandle storeContextHandle, const char *storeId, XStoreProductKind productKinds, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowAssociatedProductsUIResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowGiftingUIAsync( XStoreContextHandle storeContextHandle, const char *storeId, const char *name, const char *extendedJsonData, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowGiftingUIResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowProductPageUIAsync( const XStoreContextHandle storeContextHandle, const char *storeId, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowProductPageUIResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowPurchaseUIAsync( const XStoreContextHandle storeContextHandle, const char *storeId, const char *name, const char *extendedJsonData, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowPurchaseUIResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowRateAndReviewUIAsync( const XStoreContextHandle storeContextHandle, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowRateAndReviewUIResult( XAsyncBlock *async, XStoreRateAndReviewResult *result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowRedeemTokenUIAsync( const XStoreContextHandle storeContextHandle, const char *token, const char **allowedStoreIds, SIZE_T allowedStoreIdsCount, BOOLEAN disallowCsvRedemption, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XStoreShowRedeemTokenUIResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XStoreUnregisterGameLicenseChanged( XStoreContextHandle storeContextHandle, XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}

BOOLEAN WINAPI XStoreUnregisterPackageLicenseLost( XStoreLicenseHandle licenseHandle, XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}
