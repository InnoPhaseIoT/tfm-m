#include "psa/service.h"
#include "psa_manifest/tfm_inph_services.h"

#include "psa/error.h"
#include "psa/client.h"

#define REG_WRITE 1
#define REG_READ  2

struct inph_reg_access_req {
    uint32_t access;
    uint32_t addr;
    uint32_t val;
    uint32_t id;
};

void tfm_inph_services_partition_sfn_handler(const psa_msg_t *msg)
{
    switch (msg->type) {
        case PSA_IPC_CALL:
            {
                struct inph_reg_access_req req;

                psa_read(msg->handle, 0, &req, sizeof(req));
                if (req.access == REG_WRITE) {

                    // Validate address ranges carefully here!
                    *((volatile uint32_t *)req.addr) = req.val;

                    psa_reply(msg->handle, PSA_SUCCESS);
                }
                else if (req.access == REG_READ) {
                    uint32_t val = 0;

                    // Validate read addr carefully here!
                    val = *((volatile uint32_t *)req.addr);

                    psa_write(msg->handle, 0, &val, sizeof(val));
                    psa_reply(msg->handle, PSA_SUCCESS);
                }
                else {
                    psa_reply(msg->handle, PSA_ERROR_NOT_SUPPORTED);
                }
                break;
            }
        case PSA_IPC_CONNECT:
            psa_reply(msg->handle, PSA_SUCCESS);
            break;
        case PSA_IPC_DISCONNECT:
            psa_reply(msg->handle, PSA_SUCCESS);
            break;
        default:
            psa_reply(msg->handle, PSA_ERROR_NOT_SUPPORTED);
            break;
    }
}

psa_status_t
inph_services_sfn(const psa_msg_t *msg)
{
    tfm_inph_services_partition_sfn_handler(msg);
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
