/**
    Copyright Notice:
    Copyright 2021 DMTF. All rights reserved.
    License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
**/

/** @file
  SM3 digest Wrapper Implementations.
**/

#include "internal_crypt_lib.h"
#include <openssl/evp.h>

void *hash_md_new(void);
void hash_md_free(IN  void *md_ctx);
boolean hash_md_init(IN const EVP_MD *md, OUT void *md_ctx);
boolean hash_md_duplicate(IN const void *md_ctx, OUT void *new_md_ctx);
boolean hash_md_update(IN void *md_ctx, IN const void *data, IN uintn data_size);
boolean hash_md_final(IN void *md_ctx, OUT void *hash_value);
boolean hash_md_hash_all(IN const EVP_MD *md, IN const void *data, IN uintn data_size,
			  OUT uint8 *hash_value);

/**
  Allocates and initializes one HASH_CTX context for subsequent SM3-256 use.

  @return  Pointer to the HASH_CTX context that has been initialized.
           If the allocations fails, sm3_256_new() returns NULL.

**/
void *sm3_256_new(void)
{
  return hash_md_new();
}

/**
  Release the specified HASH_CTX context.

  @param[in]  sm3_256_ctx  Pointer to the HASH_CTX context to be released.

**/
void sm3_256_free(IN void *sm3_256_ctx)
{
  hash_md_free(sm3_256_ctx);
}

/**
  Initializes user-supplied memory pointed by sm3_context as SM3 hash context for
  subsequent use.

  If sm3_context is NULL, then return FALSE.

  @param[out]  sm3_context  Pointer to SM3 context being initialized.

  @retval TRUE   SM3 context initialization succeeded.
  @retval FALSE  SM3 context initialization failed.

**/
boolean sm3_256_init(OUT void *sm3_context)
{
  return hash_md_init (EVP_sm3(), sm3_context);
}

/**
  Makes a copy of an existing SM3 context.

  If sm3_context is NULL, then return FALSE.
  If new_sm3_context is NULL, then return FALSE.
  If this interface is not supported, then return FALSE.

  @param[in]  sm3_context     Pointer to SM3 context being copied.
  @param[out] new_sm3_context  Pointer to new SM3 context.

  @retval TRUE   SM3 context copy succeeded.
  @retval FALSE  SM3 context copy failed.
  @retval FALSE  This interface is not supported.

**/
boolean sm3_256_duplicate(IN const void *sm3_context, OUT void *new_sm3_context)
{
	return hash_md_duplicate (sm3_context, new_sm3_context);
}

/**
  Digests the input data and updates SM3 context.

  This function performs SM3 digest on a data buffer of the specified size.
  It can be called multiple times to compute the digest of long or discontinuous data streams.
  SM3 context should be already correctly initialized by sm3_init(), and should not be finalized
  by sm3_final(). Behavior with invalid context is undefined.

  If sm3_context is NULL, then return FALSE.

  @param[in, out]  sm3_context     Pointer to the SM3 context.
  @param[in]       data           Pointer to the buffer containing the data to be hashed.
  @param[in]       data_size       size of data buffer in bytes.

  @retval TRUE   SM3 data digest succeeded.
  @retval FALSE  SM3 data digest failed.

**/
boolean sm3_256_update(IN OUT void *sm3_context, IN const void *data,
		       IN uintn data_size)
{
	return hash_md_update (sm3_context, data, data_size);
}

/**
  Completes computation of the SM3 digest value.

  This function completes SM3 hash computation and retrieves the digest value into
  the specified memory. After this function has been called, the SM3 context cannot
  be used again.
  SM3 context should be already correctly initialized by sm3_init(), and should not be
  finalized by sm3_final(). Behavior with invalid SM3 context is undefined.

  If sm3_context is NULL, then return FALSE.
  If hash_value is NULL, then return FALSE.

  @param[in, out]  sm3_context     Pointer to the SM3 context.
  @param[out]      hash_value      Pointer to a buffer that receives the SM3 digest
                                  value (32 bytes).

  @retval TRUE   SM3 digest computation succeeded.
  @retval FALSE  SM3 digest computation failed.

**/
boolean sm3_256_final(IN OUT void *sm3_context, OUT uint8 *hash_value)
{
	return hash_md_final (sm3_context, hash_value);
}

/**
  Computes the SM3 message digest of a input data buffer.

  This function performs the SM3 message digest of a given data buffer, and places
  the digest value into the specified memory.

  If this interface is not supported, then return FALSE.

  @param[in]   data        Pointer to the buffer containing the data to be hashed.
  @param[in]   data_size    size of data buffer in bytes.
  @param[out]  hash_value   Pointer to a buffer that receives the SM3 digest
                           value (32 bytes).

  @retval TRUE   SM3 digest computation succeeded.
  @retval FALSE  SM3 digest computation failed.
  @retval FALSE  This interface is not supported.

**/
boolean sm3_256_hash_all(IN const void *data, IN uintn data_size,
			 OUT uint8 *hash_value)
{
  return hash_md_hash_all (EVP_sm3(), data, data_size, hash_value);
}
