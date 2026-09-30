/* Address: 00010358; name: Reset_Handler; body bytes: 16 */

/* WARNING: This function may have set the stack pointer */

void Reset_Handler(void)

{
  DAT_40050810 = 0x1ff;
  SystemInit();
  runtime_scatter_init();
  application_main();
  return;
}

