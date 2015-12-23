#include "phase_state.h"


//! Тип состояния фазы.
typedef struct _PhaseState {
    phase_t cur_phase; //!< Текущая фаза.
    drive_dir_t drive_dir; //!< Направление.
    phase_error_t phase_err; //!< Ошибка.
} phase_state_t;

static phase_state_t state;



static void phase_state_a_process(phase_t phase)
{
    drive_dir_t drive_dir;
    switch(phase){
        default:
        case PHASE_UNK:
            state.phase_err = PHASE_INVALID;
            return;
        case PHASE_A:
            state.phase_err = PHASE_BC_ERROR;
            return;
        case PHASE_B:
            drive_dir = DRIVE_DIR_FORW;
            break;
        case PHASE_C:
            drive_dir = DRIVE_DIR_BACKW;
            break;
    }
    
    if(state.drive_dir == DRIVE_DIR_UNK){
        state.drive_dir = drive_dir;
    }else if(state.drive_dir != drive_dir){
        if(state.drive_dir == DRIVE_DIR_FORW){
            state.phase_err = PHASE_B_ERROR;
        }else{//DRIVE_DIR_BACKW
            state.phase_err = PHASE_C_ERROR;
        }
    }
    
    state.cur_phase = phase;
}

static void phase_state_b_process(phase_t phase)
{
    drive_dir_t drive_dir;
    switch(phase){
        default:
        case PHASE_UNK:
            state.phase_err = PHASE_INVALID;
            return;
        case PHASE_B:
            state.phase_err = PHASE_AC_ERROR;
            return;
        case PHASE_C:
            drive_dir = DRIVE_DIR_FORW;
            break;
        case PHASE_A:
            drive_dir = DRIVE_DIR_BACKW;
            break;
    }
    
    if(state.drive_dir == DRIVE_DIR_UNK){
        state.drive_dir = drive_dir;
    }else if(state.drive_dir != drive_dir){
        if(state.drive_dir == DRIVE_DIR_FORW){
            state.phase_err = PHASE_C_ERROR;
        }else{//DRIVE_DIR_BACKW
            state.phase_err = PHASE_A_ERROR;
        }
    }
    
    state.cur_phase = phase;
}

static void phase_state_c_process(phase_t phase)
{
    drive_dir_t drive_dir;
    switch(phase){
        default:
        case PHASE_UNK:
            state.phase_err = PHASE_INVALID;
            return;
        case PHASE_C:
            state.phase_err = PHASE_AB_ERROR;
            return;
        case PHASE_A:
            drive_dir = DRIVE_DIR_FORW;
            break;
        case PHASE_B:
            drive_dir = DRIVE_DIR_BACKW;
            break;
    }
    
    if(state.drive_dir == DRIVE_DIR_UNK){
        state.drive_dir = drive_dir;
    }else if(state.drive_dir != drive_dir){
        if(state.drive_dir == DRIVE_DIR_FORW){
            state.phase_err = PHASE_A_ERROR;
        }else{//DRIVE_DIR_BACKW
            state.phase_err = PHASE_B_ERROR;
        }
    }
    
    state.cur_phase = phase;
}

void phase_state_handle(phase_t phase)
{
    switch(state.cur_phase){
        case PHASE_UNK:
            state.cur_phase = phase;
            break;
        case PHASE_A:
            phase_state_a_process(phase);
            break;
        case PHASE_B:
            phase_state_b_process(phase);
            break;
        case PHASE_C:
            phase_state_c_process(phase);
            break;
    }
}

phase_error_t phase_state_error(void)
{
    return state.phase_err;
}

phase_t phase_sate_current_phase(void)
{
    return state.cur_phase;
}

drive_dir_t phase_state_drive_direction(void)
{
    return state.drive_dir;
}

void phase_state_clear_error(void)
{
    state.phase_err = PHASE_NO_ERROR;
}

void phase_state_reset(void)
{
    state.cur_phase = PHASE_UNK;
    state.drive_dir = DRIVE_DIR_UNK;
    state.phase_err = PHASE_NO_ERROR;
}
