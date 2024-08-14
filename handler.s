.section .text
.global vector_table
.global enable_timer
.global read_timer_freq
.global set_timer_interval
.global check_timer_status
.global enable_irq

.balign 0x800
vector_table:
current_el_sp0_sync:
    b error

.balign 0x80
current_el_sp0_irq:
    b error

.balign 0x80
current_el_sp0_fiq:
    b error

.balign 0x80
current_el_sp0_serror:
    b error

.balign 0x80
current_el_spn_sync:
    b sync_handler

.balign 0x80
current_el_spn_irq:
    b irq_handler

.balign 0x80
current_el_spn_fiq:
    b error

.balign 0x80
current_el_spn_serror:
    b error

.balign 0x80
lower_el_aarch64_sync:
    b error

.balign 0x80
lower_el_aarch64_irq:
    b error

.balign 0x80
lower_el_aarch64_fiq:
    b error

.balign 0x80
lower_el_aarch64_serror:
    b error

.balign 0x80
lower_el_aarch32_sync:
    b error

.balign 0x80
lower_el_aarch32_irq:
    b error

.balign 0x80
lower_el_aarch32_fiq:
    b error

.balign 0x80
lower_el_aarch32_serror:
    b error


sync_handler:
    sub sp, sp, #256
    STP x0, x1, [sp]        
    STP x2, x3, [sp, #16]   
    STP x4, x5, [sp, #32]   
    STP x6, x7, [sp, #48]   
    STP x8, x9, [sp, #64]   
    STP x10, x11, [sp, #80] 
    STP x12, x13, [sp, #96] 
    STP x14, x15, [sp, #112]
    STP x16, x17, [sp, #128]
    STP x18, x19, [sp, #144]
    STP x20, x21, [sp, #160]
    STP x22, x23, [sp, #176]
    STP x24, x25, [sp, #192]
    STP x26, x27, [sp, #208]
    STP x28, x29, [sp, #224]
    STP x30, xzr, [sp, #240]


    mov x0, #1
    mrs x1, esr_el1
    mrs x2, elr_el1
    bl handler

    LDP x0, x1, [sp]        
    LDP x2, x3, [sp, #16]   
    LDP x4, x5, [sp, #32]   
    LDP x6, x7, [sp, #48]   
    LDP x8, x9, [sp, #64]   
    LDP x10, x11, [sp, #80] 
    LDP x12, x13, [sp, #96] 
    LDP x14, x15, [sp, #112]
    LDP x16, x17, [sp, #128]
    LDP x18, x19, [sp, #144]
    LDP x20, x21, [sp, #160]
    LDP x22, x23, [sp, #176]
    LDP x24, x25, [sp, #192]
    LDP x26, x27, [sp, #208]
    LDP x28, x29, [sp, #224]
    LDP x30, xzr, [sp, #240]

    add sp, sp, #256
    eret

irq_handler:
    sub sp, sp, #256
    STP x0, x1, [sp]        
    STP x2, x3, [sp, #16]   
    STP x4, x5, [sp, #32]   
    STP x6, x7, [sp, #48]   
    STP x8, x9, [sp, #64]   
    STP x10, x11, [sp, #80] 
    STP x12, x13, [sp, #96] 
    STP x14, x15, [sp, #112]
    STP x16, x17, [sp, #128]
    STP x18, x19, [sp, #144]
    STP x20, x21, [sp, #160]
    STP x22, x23, [sp, #176]
    STP x24, x25, [sp, #192]
    STP x26, x27, [sp, #208]
    STP x28, x29, [sp, #224]
    STP x30, xzr, [sp, #240]


    mov x0, #2
    mrs x1, esr_el1
    mrs x2, elr_el1
    bl handler

    LDP x0, x1, [sp]        
    LDP x2, x3, [sp, #16]   
    LDP x4, x5, [sp, #32]   
    LDP x6, x7, [sp, #48]   
    LDP x8, x9, [sp, #64]   
    LDP x10, x11, [sp, #80] 
    LDP x12, x13, [sp, #96] 
    LDP x14, x15, [sp, #112]
    LDP x16, x17, [sp, #128]
    LDP x18, x19, [sp, #144]
    LDP x20, x21, [sp, #160]
    LDP x22, x23, [sp, #176]
    LDP x24, x25, [sp, #192]
    LDP x26, x27, [sp, #208]
    LDP x28, x29, [sp, #224]
    LDP x30, xzr, [sp, #240]

    add sp, sp, #256
    eret

error:
    mov x0, #0
    bl handler

    eret
    

read_timer_freq:
    mrs x0, CNTFRQ_EL0
    ret

set_timer_interval:
    msr CNTP_TVAL_EL0, x0
    ret

enable_timer_register:
    mov x0, #1
    msr CNTP_CTL_EL0, x0
    ret

enable_timer:
    stp x29, x30, [sp, #-16]!
    
    bl read_timer_freq
    mov x1, #100
    udiv x0, x0, x1
    bl set_timer_interval
    bl enable_timer_register

    ldp x29, x30, [sp], #16
    ret

check_timer_status:
    mrs x0, CNTP_CTL_EL0
    ret

enable_irq:
    mov x0, #(0 << 7)
    msr daif, x0
    ret