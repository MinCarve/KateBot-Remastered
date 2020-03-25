#include "..\main.h"
#include "cvar_mgr.hpp"

cs_virtual_table cs_vt_cvar;

uintptr_t cs_virtual_table::address(void) const
{
    return self;
}

uintptr_t cs_virtual_table::function(int index)
{
    return mem->Read<uintptr_t>(mem->Read<uintptr_t>(self) + index * 4);
}

cs_virtual_table cs_interface_reg::find(const char* name)
{
    uintptr_t a0 = self, a1[30];

    do {
        mem->Read(mem->Read<uintptr_t>(a0 + 0x4), a1, sizeof(a1));
        if ((_stricmp((const char*)a1, name) >> 5) == 1)
            return mem->Read<cs_virtual_table>(mem->Read<uintptr_t>(a0) + 1);
    } while ((a0 = mem->Read<uintptr_t>(a0 + 0x8)));
    throw name;
}

cs_interface_reg interfaces::find(const char* module_name)
{
    uintptr_t v;
    v = mem->FindExport(mem->GetModulePtr(module_name), "CreateInterface");

    if (v == 0) throw module_name;

    return mem->Read<cs_interface_reg>(mem->Read<uintptr_t>(v - 0x6A));
}

cs_convar cvar::find(std::string name) {
    uintptr_t   a0;
    a0 = mem->Read<uintptr_t>(mem->Read<uintptr_t>(cs_vt_cvar.address() + 0x34));

    while ((a0 = mem->Read<uintptr_t>(a0 + 0x4))) {
        std::unique_ptr<char[]> ptr = std::make_unique<char[]>(120);
        mem->Read(mem->Read<uintptr_t>(a0 + 0xc), ptr.get(), 120);

        if (name.compare(std::string(ptr.get())) == FALSE)
            return *(cs_convar*)&a0;
    }
    return {};
}

uintptr_t cs_convar::GetPointer(void)
{
    return self;
}

cs_convar cs_convar::Next(void)
{
    int cvar = mem->Read<int>(self + 0x4);
    return *(cs_convar*)&cvar;
}

cs_convar cs_convar::Parent(void)
{
    int cvar = mem->Read<int>(self + 0x1C);
    return *(cs_convar*)&cvar;
}

std::string cs_convar::GetName(void)
{
    std::unique_ptr<char[]> ptr = std::make_unique<char[]>(120);
    mem->Read(mem->Read<uintptr_t>(self + 0xC), ptr.get(), 120);

    return std::string(ptr.get());
}

std::string cs_convar::GetDescription(void)
{
    std::unique_ptr<char[]> ptr = std::make_unique<char[]>(120);
    mem->Read(mem->Read<uintptr_t>(self + 0x10), ptr.get(), 120);

    return std::string(ptr.get());
}

int cs_convar::GetFlags(void)
{
    return mem->Read<int>(self + 0x14);
}

std::string cs_convar::GetDefaultValue(void)
{
    std::unique_ptr<char[]> ptr = std::make_unique<char[]>(120);
    mem->Read(mem->Read<uintptr_t>(self + 0x20), ptr.get(), 120);

    return std::string(ptr.get());
}

void cs_convar::SetString(std::string v)
{
    v += '\0';
    mem->Write(mem->Read<uintptr_t>(self + 0x24), v.c_str(), v.length());
}

void cs_convar::SetInt(int v)
{
    mem->Write<uint32_t>(self + 0x30, v ^ self);
}

void cs_convar::SetFloat(float v)
{
    mem->Write<uint32_t>(self + 0x2C, *(uint32_t*)&v ^ self);
}

std::string cs_convar::GetString(void)
{
    std::unique_ptr<char[]> ptr = std::make_unique<char[]>(120);
    mem->Read(mem->Read<uintptr_t>(self + 0x24), ptr.get(), 120);
       
    return std::string(ptr.get());
}

int cs_convar::GetInt(void)
{
    return mem->Read<int>(self + 0x30) ^ self;
}

float cs_convar::GetFloat(void)
{
    uint32_t v;
    v = mem->Read<uint32_t>(self + 0x2C) ^ self;
    return *(float*)&v;
}

void cvar::Init(void)
{
    auto t = interfaces::find("vstdlib.dll");
    cs_vt_cvar = t.find("VEngineCvar");
}
