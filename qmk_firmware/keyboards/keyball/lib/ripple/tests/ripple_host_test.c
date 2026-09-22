#include <assert.h>
#include <stdint.h>

#include "ripple.h"

static void test_center_and_main_ring(void) {
    ripple_state_t state;
    ripple_sample_t sample;

    ripple_state_init(&state);
    ripple_trigger(&state, 100, 32, 0, 10);

    sample = ripple_sample(&state, 0, 100, 32);
    assert(sample.intensity == 255);
    assert(sample.hue == 10);

    sample = ripple_sample(&state, 600, 220, 32);
    assert(sample.intensity == 255);
    assert(sample.hue != 10);

    sample = ripple_sample(&state, 600, 500, 500);
    assert(sample.intensity == 0);
}

static void test_trailing_ring_and_expiration(void) {
    ripple_state_t state;
    ripple_sample_t main_ring;
    ripple_sample_t trailing_ring;
    ripple_sample_t expired;

    ripple_state_init(&state);
    ripple_trigger(&state, 100, 32, 0, 20);

    main_ring = ripple_sample(&state, 600, 220, 32);
    trailing_ring = ripple_sample(&state, 600, 190, 32);
    expired = ripple_sample(&state, RIPPLE_DURATION_MS, 100, 32);

    assert(main_ring.intensity > trailing_ring.intensity);
    assert(trailing_ring.intensity > 0);
    assert(expired.intensity == 0);
}

static void test_expired_wave_does_not_reappear_after_timer_wrap(void) {
    ripple_state_t state;
    ripple_sample_t expired;
    ripple_sample_t after_wrap;

    ripple_state_init(&state);
    ripple_trigger(&state, 100, 32, 0, 20);

    expired = ripple_sample(&state, RIPPLE_DURATION_MS, 100, 32);
    after_wrap = ripple_sample(&state, 0, 100, 32);

    assert(expired.intensity == 0);
    assert(after_wrap.intensity == 0);
}

static void test_oldest_wave_is_evicted(void) {
    ripple_state_t state;
    ripple_sample_t evicted;
    ripple_sample_t newest;

    ripple_state_init(&state);
    ripple_trigger(&state, 0, 0, 0, 1);
    ripple_trigger(&state, 50, 0, 10, 2);
    ripple_trigger(&state, 100, 0, 20, 3);
    ripple_trigger(&state, 150, 0, 30, 4);
    ripple_trigger(&state, 200, 0, 40, 5);

    evicted = ripple_sample(&state, 40, 0, 0);
    newest = ripple_sample(&state, 40, 200, 0);

    assert(evicted.intensity == 0);
    assert(newest.intensity == 255);
    assert(newest.hue == 5);
}

static void test_overlapping_waves_add_intensity(void) {
    ripple_state_t one_wave;
    ripple_state_t two_waves;
    ripple_sample_t one_sample;
    ripple_sample_t two_sample;

    ripple_state_init(&one_wave);
    ripple_state_init(&two_waves);
    ripple_trigger(&one_wave, 100, 32, 0, 10);
    ripple_trigger(&two_waves, 100, 32, 0, 10);
    ripple_trigger(&two_waves, 100, 32, 0, 20);

    one_sample = ripple_sample(&one_wave, 600, 205, 32);
    two_sample = ripple_sample(&two_waves, 600, 205, 32);

    assert(two_sample.intensity > one_sample.intensity);
}

static void test_ring_covers_key_spacing(void) {
    assert(RIPPLE_RING_WIDTH >= 24);
}

int main(void) {
    test_center_and_main_ring();
    test_trailing_ring_and_expiration();
    test_expired_wave_does_not_reappear_after_timer_wrap();
    test_oldest_wave_is_evicted();
    test_overlapping_waves_add_intensity();
    test_ring_covers_key_spacing();
    return 0;
}
