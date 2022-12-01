
#include <stdint.h>
#include <stdio.h>

#include <cpuid.h> 

int main() {
  // {
  //   union {
  //     char text[16];
  //     uint32_t reg[4];
  //   } vender = {.text = {0}};
  //   uint32_t idmax = 0;
  //   // id=0: idmax=eax, VenderID:ebx.edx.ecx 
  //   __cpuid(0, idmax, vender.reg[0], vender.reg[2], vender.reg[1]);
  //   printf("%s idmax=%d\n", vender.text, idmax);
  // }
  {
    union {
      struct {
        uint8_t step: 4;
        uint8_t model: 4;
        uint8_t family: 4;
        uint8_t type: 2;
        uint8_t pad1: 2;
        uint8_t emodel: 4;
        uint8_t efamily: 8;
        uint8_t pad2: 4;
      };
      uint32_t reg;
    } eax = {.reg = 1};
    union {
      struct {
        uint8_t fpu: 1;
        uint8_t vme: 1;
        uint8_t de: 1;
        uint8_t pse: 1;
        uint8_t tsc: 1;
        uint8_t msr: 1;
        uint8_t pae: 1;
        uint8_t mce: 1;
        uint8_t cx8: 1;
        uint8_t apic: 1;
        uint8_t reserved1: 1;
        uint8_t sep: 1;
        uint8_t mtrr: 1;
        uint8_t pge: 1;
        uint8_t mca: 1;
        uint8_t cmov: 1;
        uint8_t pat: 1;
        uint8_t pse36: 1;
        uint8_t psn: 1;
        uint8_t clfsh: 1;
        uint8_t reserved2: 1;
        uint8_t ds: 1;
        uint8_t acpi: 1;
        uint8_t mmx: 1;
        uint8_t fxsr: 1;
        uint8_t sse: 1;
        uint8_t sse2: 1;
        uint8_t ss: 1;
        uint8_t htt: 1;
        uint8_t tm: 1;
        uint8_t ia64: 1;
        uint8_t pbe: 1;
      };
      uint32_t reg;
    } edx = {.reg = 0};
    union {
      struct {
        uint32_t sse3: 1;
        uint32_t pclmulqdq: 1;
        uint32_t dtes64: 1;
        uint32_t monitor: 1;
        uint32_t dscpl: 1;
        uint32_t vmx: 1;
        uint32_t smx: 1;
        uint32_t est: 1;
        uint32_t tm2: 1;
        uint32_t ssse3: 1;
        uint32_t cntxid: 1;
        uint32_t sdbg: 1;
        uint32_t fma: 1;
        uint32_t cx16: 1;
        uint32_t xtpr: 1;
        uint32_t pdcm: 1;
        uint32_t reserved1: 1;
        uint32_t pcid: 1;
        uint32_t dca: 1;
        uint32_t sse41: 1;
        uint32_t sse42: 1;
        uint32_t x2apic: 1;
        uint32_t movbe: 1;
        uint32_t popcnt: 1;
        uint32_t tscdadline: 1;
        uint32_t aes: 1;
        uint32_t xsave: 1;
        uint32_t osxsave: 1;
        uint32_t avx: 1;
        uint32_t f16c: 1;
        uint32_t rdrnd: 1;
        uint32_t hypervisor: 1;      
      };
      uint32_t reg;
    } ecx = {.reg = 0};
    uint32_t ebx = 0;
    
    __cpuid(1, eax.reg, ebx, ecx.reg, edx.reg);
    int model = (eax.family == 6 || eax.family == 15 ? eax.emodel << 4 : 0)
      + eax.model;
    int family = eax.family == 15 ? eax.efamily : eax.family;
    printf("step: %d model: %d family: %d type: %d\n", 
           eax.step, model, family, eax.type);
    printf("fpu:%d mmx:%d sse:%d sse2:%d htt:%d ia64:%d\n",
           edx.fpu, edx.mmx, edx.sse, edx.sse2, edx.htt, edx.ia64);
    printf("sse3:%d vmx:%d ssse3:%d fma:%d sse41:%d sse42:%d popcnt:%d aes:%d "
           "avx:%d hypervisor:%d\n",
           ecx.sse3, ecx.vmx, ecx.ssse3, ecx.fma, ecx.sse41, ecx.sse42,
           ecx.popcnt, ecx.aes, ecx.avx, ecx.hypervisor);
  }
  {
    union {
      struct {
        uint8_t fsgsbase: 1;
        uint8_t ia32tscadjust: 1;
        uint8_t sgx: 1;
        uint8_t bmi1: 1;
        uint8_t hle: 1;
        uint8_t avx2: 1;
        uint8_t reserved1: 1;
        uint8_t smep: 1;
        uint8_t bmi2: 1;
        uint8_t erms: 1;
        uint8_t invpcid: 1;
        uint8_t rtm: 1;
        uint8_t pqm: 1;
        uint8_t fpucsdsdeprecated: 1;
        uint8_t mpx: 1;
        uint8_t pqe: 1;
        uint8_t avx512f: 1;
        uint8_t avx512dq: 1;
        uint8_t rdseed: 1;
        uint8_t adx: 1;
        uint8_t smap: 1;
        uint8_t avx512ifma: 1;
        uint8_t pcommit: 1;
        uint8_t clflushopt: 1;
        uint8_t clwb: 1;
        uint8_t intelproctrace: 1;
        uint8_t avx512pf: 1;
        uint8_t avx512er: 1;
        uint8_t avx512cd: 1;
        uint8_t sha: 1;
        uint8_t avx512bw: 1;
        uint8_t avx512vl: 1;
      };
      uint32_t reg;
    } ebx = {.reg = 0};
    union {
      struct {
        uint8_t prefetchwt1: 1;
        uint8_t avx512vbmi: 1;
        uint32_t reserved: 30;
      };
      uint32_t reg;
    } ecx = {.reg=0};
    uint32_t edx = 0;
    uint32_t eax = 7; 
    __cpuid(7, eax, ebx.reg, ecx.reg, edx);
    printf("bmi1:%d avx2:%d bmi2:%d avx512f:%d avx512dq:%d avx512ifma:%d\n"
           "avx512pf:%d avx512er:%d avx512cd:%d sha:%d avx512bw:%d "
           "avx512vl:%d avx512vbmi:%d\n",
           ebx.bmi1, ebx.avx2, ebx.bmi2, ebx.avx512f, ebx.avx512dq,
           ebx.avx512ifma, ebx.avx512pf, ebx.avx512er, ebx.avx512cd, ebx.sha,
           ebx.avx512bw, ebx.avx512vl, ecx.avx512vbmi);
  }
  return 0;
}