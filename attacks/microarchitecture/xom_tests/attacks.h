#ifndef ATTACKS_H
#define ATTACKS_H

attack_status spectre_btb_ca_ip_test_fun(const attack_test & config);

extern "C" attack_status spectre_pht_sa_ip_test_c(uint32_t success_fraction, uint32_t num_samples);
extern "C" attack_status spectre_rsb_sa_ip_test_c(uint32_t success_fraction, uint32_t num_samples);
extern "C" attack_status meltdown_xom_c(uint32_t success_fraction, uint32_t num_samples);

static attack_status spectre_pht_sa_ip_test_fun(const attack_test & config) {
    return spectre_pht_sa_ip_test_c(config.success_fraction, config.num_samples);
}

static attack_status spectre_rsb_sa_ip_test_fun(const attack_test & config) {
    return spectre_rsb_sa_ip_test_c(config.success_fraction, config.num_samples);
}

static attack_status meltdown_xom(const attack_test & config) {
    return meltdown_xom_c(config.success_fraction, config.num_samples);
}

static attack_test spectre_btb_ca_ip = {
    spectre_btb_ca_ip_test_fun,
    "spectre-btb-ca-ip",
    "spectre",
    1,
    100,
    5
 };

static attack_test spectre_pht_sa_ip = {
    spectre_pht_sa_ip_test_fun,
    "spectre-pht-sa-ip",
    "spectre",
    1,
    0x40000,
    2
 };

static attack_test spectre_rsb_sa_ip = {
    spectre_rsb_sa_ip_test_fun,
    "spectre-rsb-sa-ip",
    "spectre",
    1,
    100,
    5
 };

static attack_test meltdown = {
    meltdown_xom,
    "meltdown-xom",
    "meltdown",
    1,
    0x10000,
    0x16
 };

#endif //ATTACKS_H
