#ifndef __CVAR_MGR__
#define __CVAR_MGR__

class cs_virtual_table {
    uintptr_t self;
public:
    uintptr_t address(void) const;
    uintptr_t function(int index);
};

extern cs_virtual_table cs_vt_cvar;

class cs_interface_reg {
    uintptr_t self;
public:
    cs_virtual_table find(const char* name);
};

namespace interfaces {
    cs_interface_reg find(const char* module_name);
};

class cs_convar {
    uintptr_t       self;
public:
    uintptr_t       GetPointer(void);
    cs_convar       Next(void);
    cs_convar       Parent(void);
    std::string     GetName(void);
    std::string     GetDescription(void);
    int             GetFlags(void);
    std::string     GetDefaultValue(void);
    std::string     GetString(void);
    int             GetInt(void);
    float           GetFloat(void);
    void            SetString(std::string v);
    void            SetInt(int v);
    void            SetFloat(float v);
};

namespace cvar {
    cs_convar find(std::string name);
    void Init(void);
}


#endif