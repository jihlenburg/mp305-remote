/* Address: 00010ee4; name: runtime_scatter_init; body bytes: 36 */

undefined * runtime_scatter_init(void)

{
  undefined4 *puVar1;
  
  for (puVar1 = &DAT_00083fa8; puVar1 < &DAT_00083fc8; puVar1 = puVar1 + 4) {
    (*(code *)puVar1[3])(*puVar1,puVar1[1],puVar1[2]);
  }
  application_main();
  return &DAT_00082da0;
}

