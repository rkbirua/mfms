"""Black-box regression tests. Requires Python 3 and GCC on PATH."""
import pathlib, subprocess, tempfile, unittest
ROOT = pathlib.Path(__file__).resolve().parents[1]
SOURCES = ['main.c','employees.c','budget.c','suppliers.c','assets.c','reports.c','validation.c']
class SystemTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory()
        cls.exe = str(pathlib.Path(cls.temp.name) / 'mfms.exe')
        subprocess.run(['gcc','-std=c99','-Wall','-Wextra','-Werror','-pedantic',*SOURCES,'-o',cls.exe],cwd=ROOT,check=True)
    @classmethod
    def tearDownClass(cls): cls.temp.cleanup()
    def run_app(self, data):
        r = subprocess.run([self.exe],input=data,text=True,capture_output=True,timeout=3)
        self.assertEqual(r.returncode,0)
        self.assertIn('Goodbye!',r.stdout)
        return r.stdout
    def test_empty_reports(self):
        out=self.run_app('5\n1\n2\n3\n4\n5\n6\n')
        for msg in ['No employees registered','No departmental budgets','No suppliers registered','No assets registered']: self.assertIn(msg,out)
    def test_menu_validation(self):
        out=self.run_app('\nabc\n0\n7\n1junk\n9999999999999999999999999999\n6 \n')
        self.assertEqual(out.count('Invalid input.'),5)
        self.assertIn('cannot be empty',out)
    def test_employee_calculations_and_search(self):
        out=self.run_app('1\n1\nAlice\nIT\n1000\n200\n100\n1\nBob\nFinance\n2000\n300\n200\n2\n3\nAlice\n3\nMissing\n4\nabc\n1\n5\n5\n1\n5\n6\n')
        for msg in ['Total Salary: N$1300.00','Total Employees: 2','Average Salary:  N$1900.00','Highest Salary:  N$2500.00','Lowest Salary:   N$1300.00','Found: ID 1','Employee not found']: self.assertIn(msg,out)
    def test_budget_totals_duplicate_and_overspend(self):
        out=self.run_app('2\n1\nIT\n1000\n1200\n1\nFinance\n2000\n500\n1\nIT\n2\n3\n4\n5\n2\n5\n6\n')
        for msg in ['already exists','EXCEEDED','Total Allocated Budget: N$3000.00','Total Expenditure:      N$1700.00','Remaining Budget:       N$1300.00','IT (over by N$200.00)']: self.assertIn(msg,out)
    def test_supplier_asset_flow(self):
        out=self.run_app('3\n1\nAcme\na@b.na\n0812345678\nWindhoek\n2\n3\nAcme\n3\nMissing\n4\n4\n1\nLaptop\nComputer\n5000\nIT\nGood\n2\n3\nLaptop\n3\nMissing\n4\n5\n3\n4\n5\n6\n')
        for msg in ['Supplier added','Asset added','Name: Acme','Name: Laptop','Value: N$5000.00','Supplier not found','Asset not found','SUPPLIER REPORT','ASSET REPORT']: self.assertIn(msg,out)
    def test_numeric_rejection(self):
        bad='-1\nabc\n12junk\nnan\ninf\n1e999\n'
        out=self.run_app('4\n1\nLaptop\nComputer\n'+bad+'5000\nIT\nGood\n4\n6\n')
        self.assertEqual(out.count('finite non-negative'),6)
        self.assertIn('Asset added',out)
    def test_employee_budget_numeric_rejection(self):
        out=self.run_app('1\n1\nAlice\nIT\n-1\n1000\ninf\n0\n2x\n0\n5\n2\n1\nIT\nnan\n100\n-2\n50\n4\n6\n')
        self.assertEqual(out.count('finite non-negative'),5)
        self.assertIn('Employee added',out); self.assertIn('Budget added',out)
    def test_blank_and_overlong_text(self):
        out=self.run_app('3\n1\n \n'+'x'*600+'\n'+'y'*50+'\nAcme\na@b.na\n081\nTown\n4\n5\n3\n5\n6\n')
        self.assertEqual(out.count('Input too long'),2)
        self.assertIn('cannot be empty',out); self.assertIn('Name: Acme',out)
    def test_eof_in_every_menu(self):
        for data in ['', '1\n','2\n','3\n','4\n','5\n']:
            with self.subTest(data=data): self.run_app(data)
    def test_eof_cancels_incomplete_records(self):
        for data,added in [('1\n1\nAlice\nIT\n','Employee added'),('2\n1\nIT\n','Budget added'),('3\n1\nAcme\n','Supplier added'),('4\n1\nLaptop\nComputer\n','Asset added')]:
            with self.subTest(data=data): self.assertNotIn(added,self.run_app(data))
    def test_capacity(self):
        record='1\nA\na@b\n081\nTown\n'
        out=self.run_app('3\n'+record*100+'1\n4\n6\n')
        self.assertEqual(out.count('Supplier added'),100)
        self.assertIn('Supplier list is full',out)
    def test_budget_within_and_equal(self):
        out=self.run_app('2\n1\nIT\n100\n100\n4\n5\n2\n5\n6\n')
        self.assertIn('WITHIN BUDGET',out);self.assertIn('None. All departments are within budget.',out)
if __name__ == '__main__': unittest.main(verbosity=2)
