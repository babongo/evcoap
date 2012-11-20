int evcoap_pdu_decode(const uint8_t *buf, size_t buf_sz, evcoap_pdu_t *pdu)
{
    assert(pdu);
    assert(buf);
    assert(buf_sz >= EVCOAP_COAP_HDR_SZ);

    /* Decode header */
    if (evcoap_hdr_decode(buf, &pdu->hdr))
        return -1;

    /* Decode options. */
    if (pdu->oc) {
        if (evcoap_opts_decode(buf + EVCOAP_COAP_HDR_SZ, pdu->opts, &opt_sz))
            return -1;
    }

    /* TODO check consistency between hdr->oc and decoded options. */

    size_t payload_offset = EVCOAP_COAP_HDR_SZ + opt_sz;

    /* Optional payload. */
    if (buf_sz > payload_offset) {
        pdu->payload_sz = buf_sz - payload_offset;
        memcpy(pdu->payload, buf + payload_offset, pdu->payload_sz);
    }

    return 0;
}

int evcoap_opts_decode(const uint8_t *buf, evcoap_opts_t *opts, size_t *opts_sz)
{
    /* TODO */
    return 0;
}

int evcoap_hdr_decode(const uint8_t *buf, evcoap_hdr_t *hdr)
{
    hdr->ver = 0;
    hdr->t = 0;
    hdr->oc = 0;
    hdr->code = 0;
    hdr->mid = 0;

    return 0;
}

