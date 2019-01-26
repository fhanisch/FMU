//cl /W3 /nologo ode.c /link /DLL /out:ode.dll
//7z a -r -tzip ode.fmu binaries modelDescription.xml

#include "fmi2Functions.h"

typedef struct {
	const fmi2CallbackFunctions *cbFcns;
	fmi2Real t;
	fmi2Real x[1];
	fmi2Real dx[1];
} Instance;

const char* fmi2GetTypesPlatform()
{
	return fmi2TypesPlatform;
}

const char* fmi2GetVersion()
{
	return fmi2Version;
}

fmi2Component fmi2Instantiate(	fmi2String  instanceName,
								fmi2Type    fmuType,
								fmi2String fmuGUID,
								fmi2String fmuResourceLocation,
								const fmi2CallbackFunctions* functions,
								fmi2Boolean visible,
								fmi2Boolean loggingOn)
{
	Instance* instance = functions->allocateMemory(1, sizeof(Instance));
	instance->cbFcns = functions;
	
	return instance;
}

void fmi2FreeInstance(fmi2Component c)
{
	((Instance*)c)->cbFcns->freeMemory(c);
}

fmi2Status fmi2SetDebugLogging(	fmi2Component c, fmi2Boolean loggingOn,
								size_t nCategories,
								const fmi2String categories[])
{
	return fmi2OK;
}

fmi2Status fmi2SetupExperiment(	fmi2Component c,
								fmi2Boolean   toleranceDefined,
								fmi2Real      tolerance,
								fmi2Real      startTime,
								fmi2Boolean   stopTimeDefined,
								fmi2Real      stopTime)
{
	return fmi2OK;
}

fmi2Status fmi2EnterInitializationMode(fmi2Component c)
{
	return fmi2OK;
}

fmi2Status fmi2ExitInitializationMode(fmi2Component c)
{
	return fmi2OK;
}

fmi2Status fmi2Terminate(fmi2Component c)
{
	return fmi2OK;
}

fmi2Status fmi2Reset(fmi2Component c)
{
	return fmi2OK;
}

fmi2Status fmi2GetReal(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Real value[])
{
	Instance *m = (Instance*)c;
	m->dx[0] = 1 - m->x[0];
	for (int i = 0; i < nvr; i++)
	{
		switch (vr[i])
		{
			case 1: value[i] = m->x[0]; break;
			case 2: value[i] = m->dx[0]; break;
		}
	}
	return fmi2OK;
}

fmi2Status fmi2SetReal(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Real value[])
{
	Instance *m = (Instance*)c;
	for (int i = 0; i < nvr; i++)
	{
		switch (vr[i])
		{
			case 1: m->x[0] = value[i]; break;
			case 2: m->dx[0] = value[i]; break;
		}
	}
	return fmi2OK;
}

fmi2Status fmi2GetFMUstate(fmi2Component c, fmi2FMUstate* FMUstate)
{
	return fmi2OK;
}
fmi2Status fmi2SetFMUstate(fmi2Component c, fmi2FMUstate  FMUstate)
{
	return fmi2OK;
}
fmi2Status fmi2FreeFMUstate(fmi2Component c, fmi2FMUstate* FMUstate)
{
	return fmi2OK;
}

fmi2Status fmi2SerializedFMUstateSize(fmi2Component c, fmi2FMUstate FMUstate, size_t *size)
{
	return fmi2OK;
}
fmi2Status fmi2SerializeFMUstate(fmi2Component c, fmi2FMUstate FMUstate, fmi2Byte serializedState[], size_t size)
{
	return fmi2OK;
}
fmi2Status fmi2DeSerializeFMUstate(fmi2Component c, const fmi2Byte serializedState[], size_t size, fmi2FMUstate* FMUstate)
{
	return fmi2OK;
}

fmi2Status fmi2GetDirectionalDerivative(fmi2Component c,
										const fmi2ValueReference vUnknown_ref[],
										size_t nUnknown,
										const fmi2ValueReference vKnown_ref[],
										size_t nKnown,
										const fmi2Real dvKnown[],
										fmi2Real dvUnknown[])
{
	return fmi2OK;
}

fmi2Status fmi2SetTime(fmi2Component c, fmi2Real time)
{
	((Instance*)c)->t = time;
	return fmi2OK;
}

fmi2Status fmi2SetContinuousStates(fmi2Component c, const fmi2Real x[], size_t nx)
{
	Instance *m = (Instance*)c;
	for (int i = 0; i < nx; i++)
	{
		m->x[i] = x[i];
	}
	return fmi2OK;
}

fmi2Status fmi2EnterEventMode(fmi2Component c)
{
	return fmi2OK;
}

fmi2Status fmi2NewDiscreteStates(fmi2Component  c, fmi2EventInfo* fmi2eventInfo)
{
	fmi2eventInfo->newDiscreteStatesNeeded = fmi2False;
	fmi2eventInfo->nextEventTimeDefined = fmi2False;
	fmi2eventInfo->nominalsOfContinuousStatesChanged = fmi2False;
	fmi2eventInfo->terminateSimulation = fmi2False;
	fmi2eventInfo->valuesOfContinuousStatesChanged = fmi2False;
	return fmi2OK;
}

fmi2Status fmi2EnterContinuousTimeMode(fmi2Component c)
{
	return fmi2OK;
}

fmi2Status fmi2CompletedIntegratorStep(	fmi2Component c,
										fmi2Boolean  noSetFMUStatePriorToCurrentPoint,
										fmi2Boolean* enterEventMode,
										fmi2Boolean* terminateSimulation)
{
	enterEventMode = fmi2False;
	terminateSimulation = fmi2False;
	return fmi2OK;
}

fmi2Status fmi2GetDerivatives(fmi2Component c, fmi2Real derivatives[], size_t nx)
{
	Instance *m = (Instance*)c;
	m->dx[0] = 1 - m->x[0];
	for (int i = 0; i < nx; i++)
	{
		derivatives[i] = m->dx[i];
	}
	return fmi2OK;
}

fmi2Status fmi2GetEventIndicators(fmi2Component c, fmi2Real eventIndicators[], size_t ni)
{
	return fmi2OK;
}

fmi2Status fmi2GetContinuousStates(fmi2Component c, fmi2Real x[], size_t nx)
{
	Instance *m = (Instance*)c;
	for (int i = 0; i < nx; i++)
	{
		x[i] = m->x[i];
	}
	return fmi2OK;
}

fmi2Status fmi2GetNominalsOfContinuousStates(fmi2Component c, fmi2Real x_nominal[], size_t nx)
{
	return fmi2OK;
}