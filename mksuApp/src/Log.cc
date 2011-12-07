/*
 * File:   Log.cc
 * Author: lpiccoli
 *
 * Created on September 28, 2010, 2:33 PM
 */

#include <iostream>

#include "Log.h"

#include "errlog.h"

int DEBUG_GENERAL_FLAG = 0;
int DEBUG_ASYN_FLAG = 0;
int DEBUG_ASYNW_FLAG = 0;
int DEBUG_COMM_FLAG = 0;
int DEBUG_COMMW_FLAG = 0;

/**
 * Log singleton initialization
 */
Log Log::_instance;
bool Log::_allLogToConsole = false;

/**
 * Default constructor.
 * 
 * @author L.Piccoli
 */
Log::Log(std::string loopName, std::string slotName) :
_logToConsole(false) {
    clear();
    _messageHeader = "fac=MKSU ";
}

/**
 * Defines if the messages are sent to the console besides being logged.
 *
 * @param log if true messages are sent to the logger and the console, false
 * means that messages will be sent to the logger only (default is true)
 * @author L.Piccoli
 */
void Log::logToConsole(bool log) {
    _logToConsole = log;
}

Log &Log::operator<<(char const *message) {
    _message << message;
    return *this;
}

Log &Log::operator<<(int const value) {
    _message << value;
    return *this;
}

Log &Log::operator<<(long int const value) {
    _message << value;
    return *this;
}

Log &Log::operator<<(double const value) {
    _message << value;
    return *this;
}

Log &Log::operator<<(LogOperatorType const operation) {
  switch (operation) {
  case cout:
    std::cout << _message.str() << std::endl;
    clear();
    break;
  case dp:
    debugPrint();
    clear();
    break;
  default:
    return *this;
  }
  return *this;
}

void Log::debugPrint() {
#ifdef  DEBUG_PRINT
  int flagLevel = 0;
  switch(_dpFlag) {
  case flagGeneral:
    flagLevel = DEBUG_GENERAL_FLAG;
    break;
  case flagAsyn:
    flagLevel = DEBUG_ASYN_FLAG;
    break;
  case flagAsynWrite:
    flagLevel = DEBUG_ASYNW_FLAG;
    break;
  case flagComm:
    flagLevel = DEBUG_COMM_FLAG;
    break;
  case flagCommWrite:
    flagLevel = DEBUG_COMMW_FLAG;
    break;
  default:
    flagLevel = 0;
  }

  if ((int) _dpLevel <= flagLevel) {
    std::cout << _message.str() << std::endl;
  }
#endif
}

Log &Log::operator<<(LogDebugPrintLevel const debugLevel) {
  _dpLevel = debugLevel;
  return *this;
}

Log &Log::operator<<(LogDebugFlag const debugFlag) {
  _dpFlag = debugFlag;
  return *this;
}

void Log::flushMessage() {
    _message << "\n";
    std::string outgoingMessage = _messageHeader + _message.str();
    if (_allLogToConsole || _logToConsole) {
        errlogPrintf(outgoingMessage.c_str());
    } else {
        errlogPrintfNoConsole(outgoingMessage.c_str());
    }
    clear();
}

void Log::clear() {
    _message.str(std::string());
    _message.clear();
    _message.seekp(0);
}

void Log::setDebugLevel(int flag, int level) {
  std::cout << "Setting flag " << flag;
  switch (flag) {
  case flagGeneral:
    DEBUG_GENERAL_FLAG = level;
    std::cout << " (GENERAL)";
    break;
  case flagAsyn:
    DEBUG_ASYN_FLAG = level;
    std::cout << " (ASYN)";
    break;
  case flagAsynWrite:
    DEBUG_ASYNW_FLAG = level;
    std::cout << " (ASYNW)";
    break;
  case flagComm:
    DEBUG_COMM_FLAG = level;
    std::cout << " (COMM)";
    break;
  case flagCommWrite:
    DEBUG_COMMW_FLAG = level;
    std::cout << " (COMMW)";
    break;
  }
  std::cout << " to level " << level << std::endl;
}

/**
 * Return the Log singleton
 *
 * @return the Log
 * @author L.Piccoli
 */
Log &Log::getInstance() {
    return _instance;
}

void Log::setAllLogToConsole(bool log) {
    _allLogToConsole = log;
}

