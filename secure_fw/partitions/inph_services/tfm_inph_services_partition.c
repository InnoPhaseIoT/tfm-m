#include "psa/service.h"
#include "psa_manifest/tfm_inph_services.h"

#include "psa/error.h"
#include "psa/client.h"

psa_status_t
inph_services_sfn(const psa_msg_t *msg)
{
    return PSA_SUCCESS;
}

void inph_services_init()
{
}

psa_status_t tfm_inph_services_partition_init(void)
{
    /* Secure Partition initialization */
    inph_services_init();

    return 0;
}
