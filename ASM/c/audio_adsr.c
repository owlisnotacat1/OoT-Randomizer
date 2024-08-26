#include "audio_adsr.h"
#define FALLTHROUGH __attribute__((fallthrough))
#define SQ(x) ((x)*(x))

AudioContext* gAudioCtx = (AudioContext*)0x80125630;
extern AdsrSubData* ADSR_SUB_DATA;

void Audio_AdsrInit(AdsrState* adsr, EnvelopePoint* envelope, s16* volOut) {
    adsr->action.asByte = 0;
    adsr->delay = 0;
    adsr->envelope = envelope;
    adsr->sustain = 0.0f;
    adsr->current = 0.0f;
    if (adsr->sub == NULL) {
        adsr->sub = ADSR_SUB_DATA;
        ADSR_SUB_DATA++;
    } else {
        adsr->sub->startCurrent = 0.0f;
        adsr->sub->startDelay = 0;
    }
    //todo figure out why this is broken
    
    // (An older versions of the audio engine used in Super Mario 64 did
    // adsr->volOut = volOut. That line and associated struct member were
    // removed, but the function parameter was forgotten and remains.)
}
// to do free sub data when done with envelope
f32 Audio_AdsrUpdate(AdsrState* adsr) {
    u8 state = adsr->action.s.state;

    switch (state) {
        case ADSR_STATE_DISABLED:
            return 0.0f;

        case ADSR_STATE_INITIAL:
            if (adsr->action.s.hang) {
                adsr->action.s.state = ADSR_STATE_HANG;
                break;
            }
            FALLTHROUGH;
        case ADSR_STATE_START_LOOP:
            adsr->envIndex = 0;
            adsr->action.s.state = ADSR_STATE_LOOP;
        retry:;
            FALLTHROUGH;
        case ADSR_STATE_LOOP:

            adsr->delay = adsr->envelope[adsr->envIndex].delay;
            adsr->sub->startCurrent = adsr->current; // Capture the starting current value for the fade
            switch (adsr->delay) {
                case ADSR_DISABLE:
                    adsr->action.s.state = ADSR_STATE_DISABLED;
                    break;

                case ADSR_HANG:
                    adsr->action.s.state = ADSR_STATE_HANG;
                    break;

                case ADSR_GOTO:
                    adsr->envIndex = adsr->envelope[adsr->envIndex].arg;
                    goto retry;

                case ADSR_RESTART:
                    adsr->action.s.state = ADSR_STATE_INITIAL;
                    break;

                default:
                    adsr->delay *= 0.75;
                    adsr->sub->startDelay = adsr->delay; // Store the original delay value
                    adsr->sub->invStartDelay = 1.0f / adsr->sub->startDelay;
                    if (adsr->delay == 0) {
                        adsr->delay = 1;
                    }
                    adsr->target = adsr->envelope[adsr->envIndex].arg / 32767.0f;
                    adsr->target = SQ(adsr->target);
                    //adsr->velocity = (adsr->target - adsr->current) / adsr->delay;
                    adsr->action.s.state = ADSR_STATE_FADE;
                    adsr->envIndex++;
                    break;
            }
            if (adsr->action.s.state != ADSR_STATE_FADE) {
                break;
            }
            FALLTHROUGH;
        case ADSR_STATE_FADE:
            f32 progress = (f32)(adsr->sub->startDelay - adsr->delay) * adsr->sub->invStartDelay;
            f32 growthFactor = 1.0f - progress;
            f32 inverseGrowth = growthFactor * growthFactor;
            adsr->current = adsr->sub->startCurrent + (adsr->target - adsr->sub->startCurrent) * (1.0f - inverseGrowth);
            adsr->delay--;
            if (adsr->delay <= 0) {
                adsr->current = adsr->target;
                adsr->action.s.state = ADSR_STATE_LOOP;
            }
            FALLTHROUGH;
        case ADSR_STATE_HANG:
            break;

        case ADSR_STATE_DECAY:
        case ADSR_STATE_RELEASE:
            adsr->current -= adsr->fadeOutVel;
            if (adsr->sustain != 0.0f && state == ADSR_STATE_DECAY) {
                if (adsr->current < adsr->sustain) {
                    adsr->current = adsr->sustain;
                    adsr->delay = 128;
                    adsr->action.s.state = ADSR_STATE_SUSTAIN;
                }
                break;
            }

            if (adsr->current < 0.00001f) {
                adsr->current = 0.0f;
                adsr->action.s.state = ADSR_STATE_DISABLED;
            }
            break;

        case ADSR_STATE_SUSTAIN:
            adsr->delay--;
            if (adsr->delay == 0) {
                adsr->action.s.state = ADSR_STATE_RELEASE;
            }
            break;
    }

    if (adsr->action.s.decay) {
        adsr->action.s.state = ADSR_STATE_DECAY;
        adsr->action.s.decay = false;
    }

    if (adsr->action.s.release) {
        adsr->action.s.state = ADSR_STATE_RELEASE;
        adsr->action.s.release = false;
    }

    if (adsr->current < 0.0f) {
        return 0.0f;
    }

    if (adsr->current > 1.0f) {
        return 1.0f;
    }

    return adsr->current;
}