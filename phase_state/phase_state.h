#ifndef PHASE_STATE_H
#define PHASE_STATE_H

/*
 * Структуры для отслеживания состояния фаз.
 */

//! Тип фазы.
typedef enum _Phase {
    PHASE_UNK = 0,
    PHASE_A = 1,
    PHASE_B = 2,
    PHASE_C = 3
} phase_t;

//! Тип направления.
typedef enum _DriveDir {
    DRIVE_DIR_UNK = 0,
    DRIVE_DIR_FORW = 1,
    DRIVE_DIR_BACKW = 2
} drive_dir_t;

//! Тип ошибки.
typedef enum _PhaseErr {
    PHASE_NO_ERROR = 0,
    PHASE_INVALID,
    PHASE_A_ERROR,
    PHASE_B_ERROR,
    PHASE_C_ERROR,
    PHASE_AB_ERROR,
    PHASE_BC_ERROR,
    PHASE_AC_ERROR
} phase_error_t;


/*
 * Функции отслеживания состояния фаз.
 */

/**
 * Обрабатывает фазу.
 * @param phase Фаза.
 */
extern void phase_state_handle(phase_t phase);

/**
 * Получает ошибку.
 * @return Ошибка.
 */
extern phase_error_t phase_state_error(void);

/**
 * Получает текущую фазу.
 * @return Текущая фаза.
 */
extern phase_t phase_sate_current_phase(void);

/**
 * Получает направление.
 * @return Направление.
 */
extern drive_dir_t phase_state_drive_direction(void);

/**
 * Получает следующую фазу после заданной при заданном направлении вращения.
 * @param phase Фаза.
 * @param dir Направление вращения.
 * @return Следующая фаза.
 */
extern phase_t phase_state_next_phase(phase_t phase, drive_dir_t dir);

/**
 * Сбрасывает ошибку.
 */
extern void phase_state_clear_error(void);

/**
 * Сбрасывает состояние.
 */
extern void phase_state_reset(void);

#endif  //PHASE_STATE_H
