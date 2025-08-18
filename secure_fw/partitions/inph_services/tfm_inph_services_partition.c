#include "psa_manifest/tfm_inph_services.h"
#include "psa/service.h"

#define BUFFER_LEN 32

static void inph_services(void)
{
    psa_msg_t msg;
    int i;
    uint8_t rec_buf[BUFFER_LEN];
    uint8_t send_buf[BUFFER_LEN] = "Hello World";

    psa_get(INPH_SERVICES_SIGNAL, &msg);
    switch (msg.type) {
    case PSA_IPC_CONNECT:
    case PSA_IPC_DISCONNECT:
        /*
         * This service does not require any setup or teardown on connect
         * or disconnect, so just reply with success.
         */
        psa_reply(msg.handle, PSA_SUCCESS);
        break;
    default:
        /* Handling services requested by psa_call. */
        if (msg.type == PSA_IPC_CALL) {
            for (i = 0; i < PSA_MAX_IOVEC; i++) {
                if (msg.in_size[i] != 0) {
                    psa_read(msg.handle, i, rec_buf, BUFFER_LEN);
                }
                if (msg.out_size[i] != 0) {
                    psa_write(msg.handle, i, send_buf, BUFFER_LEN);
                }
            }
            psa_reply(msg.handle, PSA_SUCCESS);
        } else if (msg.type == SOME_ROT_A_SERVICE_TYPE) {
            /* Operations for SOME_ROT_A_SERVICE_TYPE */
        } else {
            /* Invalid type for this Secure Partition. */
            return PSA_ERROR_PROGRAMMER_ERROR;
        }
    }
}

void inph_services_init()
{
}


void tfm_inph_services_partition_init(void)
{
    psa_signal_t signals = 0;

    /* Secure Partition initialization */
    inph_services_init();

    /*
     * Continually wait for one or more of the partition's RoT Service or
     * interrupt signals to be asserted and then handle the asserted
     * signal(s).
     */
    while (1) {
        signals = psa_wait(PSA_WAIT_ANY, PSA_BLOCK);
        if (signals & INPH_SERVICES_SIGNAL) {
            inph_services();
        } else {
            /* Should not come here */
            psa_panic();
        }
    }
}
