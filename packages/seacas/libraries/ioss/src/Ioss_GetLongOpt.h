/*
 * Copyright(C) 1999-2021 National Technology & Engineering Solutions
 * of Sandia, LLC (NTESS).  Under the terms of Contract DE-NA0003525 with
 * NTESS, the U.S. Government retains certain rights in this software.
 *
 * See packages/seacas/LICENSE for details
 */
/* S Manoharan. Advanced Computer Research Institute. Lyon. France */

#ifndef _GetLongOption_h_
#define _GetLongOption_h_

#include <iostream>

namespace Ioss {
  /** \brief A database of program command line and environment variable options and methods for
   * manipulating them.
   *
   *  A collection of long command line option names for a program that uses the Ioss library.
   */
  class GetLongOption
  {
  public:
    enum OptType { NoValue, OptionalValue, MandatoryValue };

  private:
    struct Cell
    {
      const char *option{nullptr};      // option name
      OptType     type{NoValue};        // option type
      const char *description{nullptr}; // a description of option
      const char *value{nullptr};       // value of option (string)
      const char *opt_value{
          nullptr};            // If optional value and value not entered, assign opt_value to value
      Cell *next{nullptr};     // pointer to the next cell
      bool  extra_line{false}; // True if `usage()` should output extra line at end of entry

      Cell() = default;
    };

  private:
    Cell *      table{nullptr};   // option table
    const char *ustring{nullptr}; // usage message
    char *      pname{nullptr};   // program basename
    Cell *      last{nullptr};    // last entry in option table
    int         enroll_done{0};   // finished enrolling
    char        optmarker;        // option marker

  private:
    int setcell(Cell *c, char *valtoken, char *nexttoken, const char *name);

  public:
    explicit GetLongOption(char optmark = '-');
    ~GetLongOption();

    static char *basename(char *pathname);

    int parse(int argc, char *const *argv);
    int parse(char *str, char *p);

    int         enroll(const char *opt, OptType t, const char *desc, const char *val,
                       const char *optval = nullptr, bool extra_line = false);
    const char *retrieve(const char *opt) const;
    const char *program_name() const;

    void usage(std::ostream &outfile = std::cout) const;

    /** \brief Set the program usage string.
     *
     *  The program usage string should define the command line
     *  syntax for program options and arguments and contain
     *  other helpful usage text.
     *  \param[in] str The usage string.
     */
    void usage(const char *str) { ustring = str; }
  };
} // namespace Ioss
#endif /* _GetLongOption_h_ */
