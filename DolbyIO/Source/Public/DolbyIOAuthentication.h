// Copyright 2023 Dolby Laboratories

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"

#include "Interfaces/IHttpRequest.h"

#include "DolbyIOAuthentication.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetDolbyIOTokenOutputPin, FString, Token);

UCLASS()
class DOLBYIO_API UGetDolbyIOToken : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/** Gets a Dolby.io client access token.
	 *
	 * For convenience during early development and prototyping, this function is provided to acquire an client access
	 * token directly from the game. However, please note **we do not recommend** using this mechanism in the production
	 * software for security best practices
	 * (https://docs.dolby.io/communications-apis/docs/guides-client-authentication). The app secret needs to be
	 * protected and not included in the application.
	 *
	 * @param AppKey - The app key.
	 * @param AppSecret - The app secret.
	 * @param TokenExpirationTimeInSeconds - The token's expiration time (in seconds).
	 */
	UFUNCTION(BlueprintCallable, Category = "Dolby.io Comms",
	          Meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get Dolby.io Token"))
	static UGetDolbyIOToken* GetDolbyIOToken(const FString& AppKey, const FString& AppSecret,
	                                         int TokenExpirationTimeInSeconds = 3600);

	UPROPERTY(BlueprintAssignable)
	FGetDolbyIOTokenOutputPin TokenObtained;

private:
	void Activate() override;

	void OnTokenObtained(FHttpRequestPtr, FHttpResponsePtr, bool bConnectedSuccessfully);

	FString AppKey;
	FString AppSecret;
	int TokenExpirationTimeInSeconds;
};
